import cv2
from cvzone.HandTrackingModule import HandDetector
import serial

# Replace '/dev/rfcomm0' with the correct Bluetooth serial port name for your system
ser = serial.Serial('/dev/rfcomm0', 9600)

# Get the name of the connected device
connected_device_name = ser.name

detector = HandDetector(maxHands=2, detectionCon=0.8)
video = cv2.VideoCapture(0)  # Use 0 for default webcam

while True:
    success, img = video.read()
    if not success:
        break  # Break out of the loop if capturing the frame fails

    img = cv2.flip(img, 1)

    # Find hands and landmarks
    hands, lmList = detector.findHands(img, draw=True)

    if hands:
        left_hand = hands[0] if hands[0]['type'] == 'Left' else None
        right_hand = hands[1] if len(hands) > 1 and hands[1]['type'] == 'Right' else None

        if left_hand and right_hand:
            left_fingers = detector.fingersUp(left_hand)
            right_fingers = detector.fingersUp(right_hand)

            total_fingers_left = left_fingers.count(1)
            total_fingers_right = right_fingers.count(1)

            # Print the count for each hand in the terminal
            print(f"Left hand - Number of fingers: {total_fingers_left}")
            print(f"Right hand - Number of fingers: {total_fingers_right}")

            # Send command to Arduino based on finger counts
            if total_fingers_left == 5 and total_fingers_right == 5:
                ser.write(b'F')  # Move forward
            elif total_fingers_left == 0 and total_fingers_right == 5:
                ser.write(b'L')  # Turn left
            elif total_fingers_left == 5 and total_fingers_right == 0:
                ser.write(b'R')  # Turn right
            elif total_fingers_left == 0 and total_fingers_right == 0:
                ser.write(b'B')  # Move backward
            else:
                ser.write(b'N')  # Stop

    # Display the image
    cv2.imshow("Finger Count", img)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Close the serial connection when the script ends
ser.close()
video.release()
cv2.destroyAllWindows()

# Print the name of the connected device
print("Connected device name:", connected_device_name)
