from flask import Flask, Response
import cv2
import urllib.request
import numpy as np

app = Flask(__name__)

# Replace with your IP camera stream URL
url = 'http://192.168.138.143/cam-hi.jpg'

# Function to find centroid of a contour
def find_centroid(contour):
    M = cv2.moments(contour)
    if M["m00"] != 0:
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
    else:
        cX, cY = 0, 0
    return cX, cY

def generate_frames():
    while True:
        # Read the image from the camera stream
        img_resp = urllib.request.urlopen(url)
        imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
        frame = cv2.imdecode(imgnp, -1)

        # Convert the frame to HSV
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Define the lower and upper bounds for red color
        lower_red_1 = (0, 100, 100)
        upper_red_1 = (10, 255, 255)
        mask1 = cv2.inRange(hsv_frame, lower_red_1, upper_red_1)

        lower_red_2 = (160, 100, 100)
        upper_red_2 = (180, 255, 255)
        mask2 = cv2.inRange(hsv_frame, lower_red_2, upper_red_2)

        # Join the masks to get the final mask
        mask = cv2.bitwise_or(mask1, mask2)

        # Find contours in the mask
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for contour in contours:
            # Get the bounding rectangle of each contour
            x, y, w, h = cv2.boundingRect(contour)

            # Draw the bounding rectangle
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # Find and draw centroid
            centroid_x, centroid_y = find_centroid(contour)
            cv2.circle(frame, (centroid_x, centroid_y), 5, (0, 0, 255), -1)

            # Print the coordinates of the centroid
            centroid_text = f"Target : ({centroid_x}, {centroid_y})"
            cv2.putText(frame, centroid_text, (centroid_x + 10, centroid_y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)

        # Encode the frame as JPEG
        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()

        # Yield the frame as part of the MJPEG stream
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    # Video streaming route
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
