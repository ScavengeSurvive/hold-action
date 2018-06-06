# hold-action

[![sampctl](https://shields.southcla.ws/badge/sampctl-hold--action-2f2f2f.svg?style=for-the-badge)](https://github.com/ScavengeSurvive/hold-action)

A simple progress bar wrapper that facilitates simple "hold actions". Actions
that a player must hold a key to complete.

## Installation

Simply install to your project:

```bash
sampctl package install ScavengeSurvive/hold-action
```

Include in your code and begin using the library:

```pawn
#include <hold-action>
```

## Usage

### `StartHoldAction(playerid, duration, startvalue = 0)`

- `duration` controls the length of the hold in milliseconds, this is how long
  the player must do something for to make the bar fill - usually this is
  holding down a key.
- `startvalue` controls where the hold starts in milliseconds, this is for
  starting the progress bar some way through instead of at the start.

You would normally call this function on `OnPlayerKeyStateChange` once the
player has pressed down a key required to perform some action.

### `StopHoldAction(playerid)`

This simply stops the action. This would normally be used in
`OnPlayerKeyStateChange` when the player has released the key that triggered the
`StartHoldAction` call.

This may also be used to cancel a player's action, for example of they were shot
while performing the action or an admin forced them to stop.

### `OnHoldActionUpdate(playerid, progress)`

Called every 100ms during a hold.

### `OnHoldActionFinish(playerid)`

Called when a player completes a hold, is not called when `StopHoldAction` is
used.

## Testing

To test, simply run the package:

```bash
sampctl package run
```

Connect to `localhost:7777` and hold the "Enter Vehicle" key, which is `F` or
`Enter` by default.
