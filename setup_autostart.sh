EXECUTABLE="$HOME/connect4"
SERVICE="/etc/systemd/system/connect4.service"
USER_NAME=$(whoami)

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: $EXECUTABLE not found!"
    exit 1
fi

chmod +x "$EXECUTABLE"

sudo bash -c "cat > $SERVICE" <<EOL
[Unit]
Description=Connect Four auto-start
After=network.target

[Service]
Type=simple
ExecStart=$EXECUTABLE
StandardInput=tty
StandardOutput=tty
TTYPath=/dev/tty1
Restart=on-failure
User=$USER_NAME

[Install]
WantedBy=multi-user.target
EOL

sudo systemctl daemon-reload
sudo systemctl enable connect4.service
sudo systemctl start connect4.service

echo "Systemd auto-start setup complete! Game will run on TTY1 at boot."
