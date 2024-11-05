# RoveSoCameraServer_Software

RoveSoCameraServer_Software is the dedicated software stack for operating the RoveSoCameraServer_Hardware. It supports streaming from multiple camera feeds and provides robust tools for managing camera inputs and outputs. For testing purposes, this software is compatible with `v4l2loopback` on Linux, allowing for virtual camera simulation on non-hardware setups.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Setup](#setup)
- [Usage](#usage)
- [Testing with v4l2loopback](#testing-with-v4l2loopback)
  - [Installing v4l2loopback from GitHub with Increased Device Limit](#installing-v4l2loopback-from-github-with-increased-device-limit)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## Features

- Integrates seamlessly with RoveSoCameraServer_Hardware.
- Supports simultaneous streaming from multiple cameras.
- Easily configurable for streaming unique feeds to each camera.
- Virtual testing support using `v4l2loopback` on Linux.

## Requirements

- **Operating System**: Ubuntu (tested on 24.04+)
- **Hardware**: RoveSoCameraServer_Hardware (for production use)
- **Testing Dependencies** (optional):
  - `v4l2loopback` for creating virtual cameras.
  - `ffmpeg` for streaming media files to virtual devices.

## Installation

### Install v4l2loopback (For Testing Only)

For testing purposes, you can install `v4l2loopback` using either the standard package or from the source on GitHub to increase the maximum number of virtual devices.

#### Installing from the Ubuntu Package (Up to 8 Devices)

1. Update package lists and install `v4l2loopback`:

    ```bash
    sudo apt update
    sudo apt install v4l2loopback-dkms v4l2loopback-utils
    ```

2. Load `v4l2loopback` with up to 8 virtual devices:

    ```bash
    sudo modprobe v4l2loopback devices=8 video_nr=0,1,2,3,4,5,6,7 exclusive_caps=1
    ```

#### Installing v4l2loopback from GitHub with Increased Device Limit

To support more than 8 virtual devices, follow these steps to install `v4l2loopback` from source and modify the maximum device limit:

1. Clone the `v4l2loopback` GitHub repository:

    ```bash
    git clone https://github.com/umlaeute/v4l2loopback.git
    cd v4l2loopback
    ```

2. Open `v4l2loopback.c` in a text editor and modify the maximum device limit:

    ```bash
    nano v4l2loopback.c
    ```

3. Find the line that defines `VIDEO_MAX_DEVICES`, which usually looks like this:

    ```c
    #define VIDEO_MAX_DEVICES 8
    ```

4. Change `8` to `10` (or any other desired limit):

    ```c
    #define VIDEO_MAX_DEVICES 10
    ```

5. Save and close the file.

6. Build and install `v4l2loopback`:

    ```bash
    make
    sudo make install
    sudo depmod -a
    ```

7. Load `v4l2loopback` with 10 virtual devices:

    ```bash
    sudo modprobe v4l2loopback devices=10 video_nr=0,1,2,3,4,5,6,7,8,9 exclusive_caps=1
    ```

### Install ffmpeg (For Testing Only)

Install `ffmpeg` if not already installed:

```bash
sudo apt install ffmpeg
```

## Setup

1. Clone the `RoveSoCameraServer_Software` repository:

    ```bash
    git clone --recurse-submodules -j8 https://github.com/MissouriMRDT/RoveSoCameraServer_Software.git
    cd RoveSoCameraServer_Software
    ```

2. Prepare your media files (for testing purposes):
    - Store images or videos you want to stream in a dedicated folder, such as `media/`.
    - Ensure they are named sequentially, e.g., `image0.jpg`, `image1.jpg`, etc., for easy configuration.

## Usage

### Running on RoveSoCameraServer_Hardware

To deploy and run RoveSoCameraServer_Software on RoveSoCameraServer_Hardware, follow the specific hardware configuration instructions provided in the hardware documentation.

### Testing with v4l2loopback

If RoveSoCameraServer_Hardware is unavailable, you can simulate streams on Linux using `v4l2loopback` and `ffmpeg`.

#### Starting the Camera Streams

To stream images to each virtual camera:

```bash
nohup ffmpeg -re -loop 1 -i media/image0.jpg -vf format=yuv420p -f v4l2 /dev/video0 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image1.jpg -vf format=yuv420p -f v4l2 /dev/video1 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image2.jpg -vf format=yuv420p -f v4l2 /dev/video2 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image3.jpg -vf format=yuv420p -f v4l2 /dev/video3 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image4.jpg -vf format=yuv420p -f v4l2 /dev/video4 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image5.jpg -vf format=yuv420p -f v4l2 /dev/video5 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image6.jpg -vf format=yuv420p -f v4l2 /dev/video6 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image7.jpg -vf format=yuv420p -f v4l2 /dev/video7 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image8.jpg -vf format=yuv420p -f v4l2 /dev/video8 > /dev/null 2>&1 &
nohup ffmpeg -re -loop 1 -i media/image9.jpg -vf format=yuv420p -f v4l2 /dev/video9 > /dev/null 2>&1 &
```

Repeat for each virtual camera, modifying the image and device as needed.

#### Verifying Streams

Use `ffplay` to verify each virtual camera:

```bash
ffplay /dev/video0
```

### Stopping the Streams

To stop all `ffmpeg` processes:

```bash
killall ffmpeg
```

## Troubleshooting

- **Empty Streams**: Ensure `ffmpeg` is configured with `-vf format=yuv420p`, as `v4l2loopback` may require specific formats.
- **Device Limitations**: `v4l2loopback` may limit the number of devices. Modify settings as needed for testing.

## License

This project is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for details.
