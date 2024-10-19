import cv2
import urllib.request
import numpy as np

# Replace the URL with the IP camera's stream URL
# url = 'http://192.168.243.45/cam-hi.jpg'
url = 'http://192.168.138.143/cam-hi.jpg'
cv2.namedWindow("live Cam Testing", cv2.WINDOW_AUTOSIZE)


# Function to find centroid of a contour
def find_centroid(contour):
    M = cv2.moments(contour)
    if M["m00"] != 0:
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
    else:
        cX, cY = 0, 0
    return cX, cY



# Create a VideoCapture object
cap = cv2.VideoCapture(url)

# Check if the IP camera stream is opened successfully
if not cap.isOpened():
    print("Failed to open the IP camera stream")
    exit()

# Read and display video frames
while True:
    # Read a frame from the video stream
    img_resp=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    #ret, frame = cap.read()
    frame = cv2.imdecode(imgnp,-1)


   
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Define the lower and upper bounds for red color
    lower_red = (0, 100, 100)
    upper_red = (10, 255, 255)
    mask1 = cv2.inRange(hsv_frame, lower_red, upper_red)

    lower_red = (160, 100, 100)
    upper_red = (180, 255, 255)
    mask2 = cv2.inRange(hsv_frame, lower_red, upper_red)

    # Joining the masks to get the final mask
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
        centroid_text = f"Centroid: ({centroid_x}, {centroid_y})"
        print(centroid_text)
        # cv2.putText(frame, centroid_text, (centroid_x + 10, centroid_y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)


    # Display the frame
    cv2.imshow('Video', frame)



    cv2.imshow('live Cam Testing',frame)
    key=cv2.waitKey(5)
    if key==ord('q'):
        break
    

cap.release()
cv2.destroyAllWindows()