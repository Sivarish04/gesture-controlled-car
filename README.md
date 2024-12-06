# Gesture Controlled Car using OpenCV and Bluetooth

This project allows you to control a car using hand gestures with two hands, through a camera (using OpenCV for hand tracking) and a Bluetooth communication module (HC-05). The project uses an Arduino board to control a car's movement via motors and receives commands through Bluetooth.

### Features:
- Use of **OpenCV** and **cvzone**'s **HandTrackingModule** for detecting hand gestures.
- Bluetooth communication with **HC-05 Bluetooth module**.
- Control car movement (forward, left, right, backward, stop) based on hand gestures.
- Compatible with **Arduino** and **L298N Motor Driver**.

### Components Used:
- **Arduino Uno** (or any other compatible Arduino board)
- **L298N Motor Driver**
- **HC-05 Bluetooth Module**
- **2 DC Motors**
- **Camera (for hand gesture tracking)**
- **Jumper Wires**

### Libraries Required:
- `cv2` (OpenCV)
- `cvzone`
- `serial` (PySerial)

### Installation:
1. Install the required libraries for Python:
   ```bash
   pip install opencv-python cvzone pyserial

