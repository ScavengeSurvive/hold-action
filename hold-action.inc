#include <a_samp>
#include <progress2>
#include <YSI\y_timers>
#include <YSI\y_colours>
#include <YSI\y_hooks>


static
	PlayerBar:ActionBar = INVALID_PLAYER_BAR_ID,
	HoldActionLimit[MAX_PLAYERS],
	HoldActionProgress[MAX_PLAYERS],
	Timer:HoldActionTimer[MAX_PLAYERS],
	HoldActionState[MAX_PLAYERS];


forward OnHoldActionUpdate(playerid, progress);
forward OnHoldActionFinish(playerid);


stock StartHoldAction(playerid, duration, startvalue = 0) {
	if(HoldActionState[playerid] == 1) {
		return 1;
	}

	stop HoldActionTimer[playerid];
	HoldActionTimer[playerid] = repeat HoldActionUpdate(playerid);

	HoldActionLimit[playerid] = duration;
	HoldActionProgress[playerid] = startvalue;
	HoldActionState[playerid] = 1;

	SetPlayerProgressBarMaxValue(playerid, ActionBar, HoldActionLimit[playerid]);
	SetPlayerProgressBarValue(playerid, ActionBar, HoldActionProgress[playerid]);
	ShowPlayerProgressBar(playerid, ActionBar);

	return 0;
}

stock StopHoldAction(playerid) {
	if(HoldActionState[playerid] == 0) {
		return 1;
	}

	stop HoldActionTimer[playerid];
	HoldActionLimit[playerid] = 0;
	HoldActionProgress[playerid] = 0;
	HoldActionState[playerid] = 0;

	HidePlayerProgressBar(playerid, ActionBar);

	return 0;
}

timer HoldActionUpdate[100](playerid) {
	if(HoldActionProgress[playerid] >= HoldActionLimit[playerid]) {
		StopHoldAction(playerid);
		CallLocalFunction("OnHoldActionFinish", "d", playerid);
		return;
	}

	SetPlayerProgressBarMaxValue(playerid, ActionBar, HoldActionLimit[playerid]);
	SetPlayerProgressBarValue(playerid, ActionBar, HoldActionProgress[playerid]);
	ShowPlayerProgressBar(playerid, ActionBar);

	CallLocalFunction("OnHoldActionUpdate", "dd", playerid, HoldActionProgress[playerid]);

	HoldActionProgress[playerid] += 100;

	return;
}

hook OnPlayerConnect(playerid) {
	ActionBar = CreatePlayerProgressBar(playerid, 291.0, 345.0, 57.50, 5.19, X11_GREY, 100.0);
}

hook OnPlayerDisconnect(playerid, reason) {
	DestroyPlayerProgressBar(playerid, ActionBar);
}
