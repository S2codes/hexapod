import cv2
import urllib.request
import numpy as np

# Replace the URL with the IP camera's stream URL
url = 'http://192.168.140.140/cam-hi.jpg'
cv2.namedWindow("live Cam Testing", cv2.WINDOW_AUTOSIZE)

# Define the codec and create a VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'mp4v')  # Codec for MP4 files
out = cv2.VideoWriter('data_output3.mp4', fourcc, 20.0, (640, 480))  # Adjust FPS and resolution as needed

while True:
    # Read a frame from the video stream
    img_resp = urllib.request.urlopen(url)
    imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
    frame = cv2.imdecode(imgnp, -1)

    # Check if frame was received successfully
    if frame is None:
        print("Failed to retrieve frame")
        break

    # Resize frame to ensure consistent dimensions
    frame_resized = cv2.resize(frame, (640, 480))  # Adjust resolution as per your requirement

    # Flip the frame vertically and horizontally
    frame_flipped = cv2.flip(frame_resized, -1)  # -1 flips both vertically and horizontally

    # Write the flipped frame to the video file
    out.write(frame_flipped)

    # Display the flipped frame
    cv2.imshow('live Cam Testing', frame_flipped)
    
    # Break loop on 'q' key press
    key = cv2.waitKey(5)
    if key == ord('q'):
        break

# Release resources
out.release()
cv2.destroyAllWindows()
