
path=plots/May29

key=0jet_125_CR_QCDrich_notOS_TrkFit

# geometry default: 120x120

# montage +frame +shadow +label -tile 4x4  -geometry 50x50+0+0 $path/*.png $key.png
# montage +frame +shadow +label -tile 3x4   $path/*.png $key.png
# montage +frame +shadow +label -tile 2x4  -geometry 240x240+8+8 $path/*.png $key.png
# montage  -mode concatenate -tile 2x3  -geometry +8+8  -shadow $path/*.png $key.png


montage  -mode concatenate -tile 2x3  -geometry +8+8  $path/*$key*.png $key.png

convert $key*.png $key.pdf