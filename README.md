![](./docs/images/banner.png)

# Overview
The [Stretch Firmware](https://github.com/hello-robot/stretch_firmware) repository provides the Arduino based firmware for the Stretch robot. 

Minor version updates to Stretch Body may occasionally require the robot's firmware to also be updated.

The repository includes the firmware for the three Stretch PCBA types: 

* hello_stepper: firmware for stepper motor controller based on the Mechaduino project
* hello_wacc: firmware for wrist accelerometer board (Wacc) in the wrist 
* hello_pimu:  firmware for power and imu board (Pimu) in the base

## Releasing New Firmware

If you're a maintainer for this repo, follow these steps to release new firmware. Stretch users will be able to use the [`REx_firmware_updater.py` CLI](https://docs.hello-robot.com/0.3/software/updating_software/#firmware) to install the new release.

 1. Review and merge a pull request into the main branch. In the PR, ensure that you increment the version/protocol of the firmwares (hello_stepper, hello_wacc, hello_pimu) that received changes. You can do this by changing `#define FIRMWARE_VERSION "Pimu.v0.0.5p0"` in the firmware's Common.h file. When updating the protocol version increment the <Minor> version as well, for example, Pimu.v0.0.5p0 --> Pimu.v0.1.0p1
 2. Clone the firmware locally
    ```
    gh repo clone hello-robot/stretch_firmware
    ```
 3. Tag with the full version name that matches Common.h , eg
    ```
    git tag -a Pimu.v0.0.5p0 -m "Pimu bugfix of foo"
    ```
 4. Push the tag to Github
    ```
    git push origin --tags
    ```
 5. Ensure the new firmware is detected by the updater CLI
    ```
    REx_firmware_updater.py --recommended
    ```

## License
For details, see the LICENSE.md file in the root directory. All materials within this repository are licensed with the [GNU General Public License v3.0 (GNU GPLv3)](https://www.gnu.org/licenses/gpl-3.0.html) except where other third-party licenses must apply.  

We thank people who have contributed to this work via open-source code and open hardware. We especially thank the [Mechaduino](https://tropical-labs.com/mechaduino/) project and [Tropical Labs](https://tropical-labs.com/). The motor controller firmware and hardware are derived from the excellent [firmware](https://github.com/jcchurch13/Mechaduino-Firmware) and [hardware](https://github.com/jcchurch13/Mechaduino-Hardware) created for the Mechaduino project by Tropical Labs.

------
<div align="center"> All materials are Copyright 2022-2024 by Hello Robot Inc. Hello Robot and Stretch are registered trademarks. The Stretch robots are covered by U.S. Patent 11,230,000 and other patents pending.</div>

