$${\color{#a80707}\huge\mathtt{Robotic Arm}}$$

<div align="center">
3D printed robotic arm for gesture-based control using wearable gloves.

</div>

---

This project is a gesture-controlled robotic arm operated using gloves. The left glove uses **analog flex sensors** to detect finger bending for controlling the arm joints and gripper, while the right glove uses an **MPU-6050 IMU** to capture hand orientation through acceleration and gyroscope data. An **Arduino Nano** processes the sensor inputs and transmits them serially to an **Arduino Uno**, which maps the gestures to servo positions and drives the robotic arm in real time.

---

## Video Showcase

### Glove Control Demo

<p align="center">
  <video controls width="35%" src="assets/gloveFlex.mov">
    <source src="assets/gloveFlex.mov" type="video/quicktime">
    <source src="assets/gloveFlex.mov" type="video/mp4">
  </video>
</p>

### Flex Sensor Setup

Testing bend response thresholds and LED feedback indicators:

<table>
  <tr>
    <th width="50%" align="center">Red Flex Sensor</th>
    <th width="50%" align="center">Green Flex Sensor</th>
  </tr>
  <tr>
    <td align="center">
      <video controls width="100%" src="assets/redFlex.MP4">
        <source src="assets/redFlex.MP4" type="video/mp4">
      </video>
    </td>
    <td align="center">
      <video controls width="100%" src="assets/greenFlex.MP4">
        <source src="assets/greenFlex.MP4" type="video/mp4">
      </video>
    </td>
  </tr>
</table>

### Servo Wiring and Test

Verifying 4-DOF servo movement, limits, and wiring before full integration:

<p align="center">
  <video controls width="50%" src="assets/servoTest.MP4">
    <source src="assets/servoTest.MP4" type="video/mp4">
  </video>
</p>

---

## Assembly

<p align="center">
  <img src="assets/assembly1.jpg" alt="Robotic Arm Assembly 1" width="38%" />
  <img src="assets/assembly2.jpg" alt="Robotic Arm Assembly 2" width="38%" />
</p>

---

## Acknowledgements

- [Inspiration](https://youtu.be/F0ZvF-FbCr0?si=jibcifKu784Cr1pa)
- [Robotic Arm used](https://youtu.be/xILy-UI7aAQ)
