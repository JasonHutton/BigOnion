#pragma once

#include <string>
#include <vector>

using namespace std;

namespace KeyInput
{
	// these are the key numbers that are used by the key system
	// normal keys should be passed as lowercased ascii
	// Some high ascii (> 127) characters that are mapped directly to keys on
	// western european keyboards are inserted in this table so that those keys
	// are bindable (otherwise they get bound as one of the special keys in this
	// table)
	enum keyNum_t
	{
		K_TAB = 9,
		K_ENTER = 13,
		K_ESCAPE = 27,
		K_SPACE = 32,

		K_BACKSPACE = 127,

		K_COMMAND = 128,
		K_CAPSLOCK,
		K_SCROLL,
		K_POWER,
		K_PAUSE,

		K_UPARROW = 133,
		K_DOWNARROW,
		K_LEFTARROW,
		K_RIGHTARROW,

		// The 3 windows keys
		K_LWIN = 137,
		K_RWIN,
		K_MENU,

		K_ALT = 140,
		K_CTRL,
		K_SHIFT,
		K_INS,
		K_DEL,
		K_PGDN,
		K_PGUP,
		K_HOME,
		K_END,

		K_F1 = 149,
		K_F2,
		K_F3,
		K_F4,
		K_F5,
		K_F6,
		K_F7,
		K_F8,
		K_F9,
		K_F10,
		K_F11,
		K_F12,
		K_INVERTED_EXCLAMATION = 161,	// upside down !
		K_F13,
		K_F14,
		K_F15,

		K_KP_HOME = 165,
		K_KP_UPARROW,
		K_KP_PGUP,
		K_KP_LEFTARROW,
		K_KP_5,
		K_KP_RIGHTARROW,
		K_KP_END,
		K_KP_DOWNARROW,
		K_KP_PGDN,
		K_KP_ENTER,
		K_KP_INS,
		K_KP_DEL,
		K_KP_SLASH,
		K_SUPERSCRIPT_TWO = 178,		// superscript 2
		K_KP_MINUS,
		K_ACUTE_ACCENT = 180,			// accute accent
		K_KP_PLUS,
		K_KP_NUMLOCK,
		K_KP_STAR,
		K_KP_EQUALS,

		K_MASCULINE_ORDINATOR = 186,
		// K_MOUSE enums must be contiguous (no char codes in the middle)
		K_MOUSE1 = 187,
		K_MOUSE2,
		K_MOUSE3,
		K_MOUSE4,
		K_MOUSE5,
		K_MOUSE6,
		K_MOUSE7,
		K_MOUSE8,

		K_MWHEELDOWN = 195,
		K_MWHEELUP,

		K_JOY1 = 197,
		K_JOY2,
		K_JOY3,
		K_JOY4,
		K_JOY5,
		K_JOY6,
		K_JOY7,
		K_JOY8,
		K_JOY9,
		K_JOY10,
		K_JOY11,
		K_JOY12,
		K_JOY13,
		K_JOY14,
		K_JOY15,
		K_JOY16,
		K_JOY17,
		K_JOY18,
		K_JOY19,
		K_JOY20,
		K_JOY21,
		K_JOY22,
		K_JOY23,
		K_JOY24,
		K_JOY25,
		K_JOY26,
		K_JOY27,
		K_GRAVE_A = 224,	// lowercase a with grave accent
		K_JOY28,
		K_JOY29,
		K_JOY30,
		K_JOY31,
		K_JOY32,

		K_AUX1 = 230,
		K_CEDILLA_C = 231,	// lowercase c with Cedilla
		K_GRAVE_E = 232,	// lowercase e with grave accent
		K_AUX2,
		K_AUX3,
		K_AUX4,
		K_GRAVE_I = 236,	// lowercase i with grave accent
		K_AUX5,
		K_AUX6,
		K_AUX7,
		K_AUX8,
		K_TILDE_N = 241,	// lowercase n with tilde
		K_GRAVE_O = 242,	// lowercase o with grave accent
		K_AUX9,
		K_AUX10,
		K_AUX11,
		K_AUX12,
		K_AUX13,
		K_AUX14,
		K_GRAVE_U = 249,	// lowercase u with grave accent
		K_AUX15,
		K_AUX16,

		K_PRINT_SCR = 252,	// SysRq / PrintScr
		K_RIGHT_ALT = 253,	// used by some languages as "Alt-Gr"
		K_LAST_KEY = 254	// this better be < 256!
	};

	static const unsigned char s_scantokey[256] = {
		//  0            1       2          3          4       5            6         7
		//  8            9       A          B          C       D            E         F
			0,           27,    '1',       '2',        '3',    '4',         '5',      '6',
			'7',        '8',    '9',       '0',        '-',    '=',          K_BACKSPACE, 9, // 0
			'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
			'o',        'p',    '[',       ']',        K_ENTER,K_CTRL,      'a',      's',   // 1
			'd',        'f',    'g',       'h',        'j',    'k',         'l',      ';',
			'\'',       '`',    K_SHIFT,   '\\',       'z',    'x',         'c',      'v',   // 2
			'b',        'n',    'm',       ',',        '.',    '/',         K_SHIFT,  K_KP_STAR,
			K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
			K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
			K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
			K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           0,        K_F11,
			K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
			0,          0,      0,         0,          0,      0,           0,        0,
			0,          0,      0,         0,          0,      0,           0,        0,     // 6
			0,          0,      0,         0,          0,      0,           0,        0,
			0,          0,      0,         0,          0,      0,           0,        0,      // 7
		// shifted
			0,           27,    '!',       '@',        '#',    '$',         '%',      '^',
			'&',        '*',    '(',       ')',        '_',    '+',          K_BACKSPACE, 9, // 0
			'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
			'o',        'p',    '[',       ']',        K_ENTER,K_CTRL,      'a',      's',   // 1
			'd',        'f',    'g',       'h',        'j',    'k',         'l',      ';',
			'\'',       '~',    K_SHIFT,   '\\',       'z',    'x',         'c',      'v',   // 2
			'b',        'n',    'm',       ',',        '.',    '/',         K_SHIFT,  K_KP_STAR,
			K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
			K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
			K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
			K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           0,        K_F11,
			K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
			0,          0,      0,         0,          0,      0,           0,        0,
			0,          0,      0,         0,          0,      0,           0,        0,     // 6
			0,          0,      0,         0,          0,      0,           0,        0,
			0,          0,      0,         0,          0,      0,           0,        0      // 7
	};

	enum usercmdButton_t
	{
		UB_NONE,

		//UB_TOGGLECONSOLE,

		//UB_SELECT_NEXT,
		//UB_SELECT_PREV,
		//UB_LOG_GLEXTENSIONS,
		UB_FORCE_QUIT,

		UB_MOVE_FORWARD,
		UB_MOVE_BACKWARD,
		UB_MOVE_LEFT,
		UB_MOVE_RIGHT,

		//UB_ROT_UP,
		//UB_ROT_DOWN,
		//UB_ROT_LEFT,
		//UB_ROT_RIGHT,

		//UB_SCREENSHOT,

		UB_MAX_BUTTONS
	};

	struct userCmdString_t
	{
		const char* string;
		usercmdButton_t	button;
	};
}

namespace KeyInput
{
	const unsigned char* Sys_GetScanTable();
	int	MapKey(int key);
	const int GetKeyNumForName(const string& name);
	const usercmdButton_t& GetButtonForName(const string& name);
	const string GetKeyNameForNum(const int& keynum);
	const string GetNameForButton(const usercmdButton_t& button);
}