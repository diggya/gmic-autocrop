#!/bin/sh

CRD=`./autocrop $1`

gmic -input $1 \
  -crop[0] $CRD \
  -output crop.jpg

gmic -input crop.jpg [-1,0] \
  -resize2dy[0] 300 \
  -crop[0] {w/h*300/2-149},0,{w/h*300/2+150},299 \
  -blur[0] 5 \
  -resize2dx[1] 300 \
  -image[0] [-1],0,{150-h/2} \
  -keep[0] \
  -output thumb.jpg
