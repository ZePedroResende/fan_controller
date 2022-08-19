# Fan controller

This is for msi laptops that don't have the actual fan boost button.

You need to enable this module `sudo modprobe ec_sys write_support=1`.

You can enable or disable the boost by passing a 1 or a 0 to the cli. If you
dont pass it it will simply display the current temparature of the cpu and gpu.

The constants where removed from the [mlfc](https://github.com/marshevms/mlfc)
project. I just wanted a simple cli instead of a server and client with dbus.
