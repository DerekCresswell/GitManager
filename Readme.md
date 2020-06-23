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
