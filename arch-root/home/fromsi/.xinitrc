wal -R &
[[ -f ~/.Xresources ]] && xrdb -merge -I$HOME ~/.Xresources &
bash $HOME/.config/polybar/launch.sh &
exec i3
