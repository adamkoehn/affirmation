# Affirmation

Affirmation is a completely unnecessary program written as part of the
Unnecessary Program project. It will attempt to run as a daemon by default,
and provide a libnotify notification telling you that you are doing a great
job at a regular interval. However, if you have any ideas for features or any
bug reports, feel free to contribute.

## Requirements

Affirmation is currently written for Linux with libnotify. If you want this
program on another platform, feel free to ask. If I get enough interest, I
might be bothered to add support for it.

## Install

I'm not a C programmer professionally, I'm still learning autotools, but
this is an autotools project. I've decided to require the use of autoreconf
for now because I'm not entirely sure what I want to do with this yet.

```bash
autoreconf -i
./configure
make
sudo make install
```

## Road Map

I have a few ideas for new changes that may or may not include the following.

1. Web service to download affirmations
2. Proper autotools distribution instead of requiring autoreconf

If you have any ideas feel free to contribute.