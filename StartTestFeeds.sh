#!/bin/bash

# Start test feeds for camera server
# NOTE: Resizes feeds to 1280x720 @ 30 fps to match the server's expected input format.
# NOTE: This particular script was written only for GIFs.
for i in {0..7}; do
    nohup ffmpeg -re -stream_loop -1 \
        -i "media/video${i}.gif" \
        -vf "scale=1280:720:force_original_aspect_ratio=decrease,pad=1280:720:(ow-iw)/2:(oh-ih)/2,format=yuv420p" \
        -r 30 \
        -pix_fmt yuv420p \
        -f v4l2 "/dev/video${i}" \
        > "/tmp/video${i}-ffmpeg.log" 2>&1 &
done