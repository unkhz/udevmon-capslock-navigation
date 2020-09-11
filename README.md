# udevmon-capslock-navigation

Interception plugin for mapping `capslock` to navigation keys near the home row:

- j -> left
- k -> down
- i -> up
- l -> right
- capslock up+down is translated to esc up+down

## What is it?

Yet another plugin for interception tools to recreate some functionality of a MacOS karabiner setup. The purpose is to
recapture the useless caps-lock key for something useful. In this case it's the ESC key and arrow navigation.

Built on top of these two existing plugins

- https://github.com/kbairak/s2arrows
- https://gitlab.com/interception/linux/plugins/caps2esc

## Dependencies

- [Interception Tools][interception-tools]

## Building

```sh
git clone git@github.com:unkhz/udevmon-capslock-navigation
cd udevmon-capslock-navigation
mkdir build
cd build
cmake ..
make
sudo make install
```

## Enabling

### udevmon

`udevmon-capslock-navigation` is an [_Interception Tools_][interception-tools] plugin. A suggested
`udevmon` job configuration (`/etc/udevmon.yaml`) is:

```yaml
- JOB: "intercept -g $DEVNODE | udevmon-capslock-navigation | uinput -d $DEVNODE"
  DEVICE:
    EVENTS:
      EV_KEY:
        [
          KEY_CAPSLOCK,
          KEY_ESC,
          KEY_I,
          KEY_J,
          KEY_K,
          KEY_L,
          KEY_LEFT,
          KEY_DOWN,
          KEY_UP,
          KEY_RIGHT,
        ]
```

### systemd

A suggested systemd service to run udevmon can be setup by creating the
following file (`/etc/systemd/udevmon.service`):

```ini
[Unit]
Description=udevmon
After=systemd-user-sessions.service

[Service]
ExecStart=/usr/bin/nice -n -20 usr/local/bin/udevmon -c /etc/udevmon.yaml

[Install]
WantedBy=multi-user.target
```

Then, you can enable and start the service like any other:

```sh
sudo systemctl enable --now udevmon.service
```

## License

<a href="https://gitlab.com/interception/linux/plugins/caps2esc/blob/master/LICENSE.md">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/License_icon-mit-2.svg/120px-License_icon-mit-2.svg.png" alt="MIT">
</a>

[s2arrows]: https://github.com/kbairak/s2arrows
[caps2esc]: https://gitlab.com/interception/linux/plugins/caps2esc
[interception-tools]: https://gitlab.com/interception/linux/tools
