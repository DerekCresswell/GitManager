# GitManager

A tool to let you quickly switch git configurations.

Often you can have an email for your work and one for your personal git accounts. It can be annoying to remember and switch your configurations.
This tool aims to give you a simple way to create and store git "profiles" that you can switch between for any given repo.

## Usage

*Currently, not all intended features are implemented.*

Adding a profile to your list :

```
gitmanager add <nameOfProfile>
```

List avaliable profiles :

```
gitmanager list
```

Setting a profile on the current repo :

```
gitmanager set <nameOfProfile>
```

You can use the `-v` option to show verbose messages during execution.

## Building

Make sure to download the submodules when cloning this repo.

```
git clone --recursive https://github.com/DerekCresswell/GitManager.git
```

This tool can be easily built with Cmake.

```
mkdir build
cd build
cmake ..
```

## Configuration

This tool uses the [TOML](https://toml.io/) specification to store configuration. The configuration is per user and can be found at :

* Linux, `~/.gitmanager`

To declare a profile it should follow the syntax shown here :

```
[profileName]
description = "Use this profile for XYZ"
userName = "myUserName"
userEmail = "myemail@github.com"
```

It is important to note that you must also put the name of the profile in an array called `profileNames`. This is used for discovery.

```
profileNames = [
    "profileName",
]
```
