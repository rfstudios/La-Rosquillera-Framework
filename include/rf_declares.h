
/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef RF_DECLARES_H
#define RF_DECLARES_H

enum RF_KeyCode{
    _a,_b,_c,_d,_e,_f,_g,_h,_i,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,_x,_y,_z,
    _1,_2,_3,_4,_5,_6,_7,_8,_9,_0,
    _return,_esc,_backspace,_tab,_space,
    _FOO_KEY
};
/*enum keyCode{
    _esc,
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _0,
    _minus, _plus,
    _backspace,
    _tab,
    _q, _w, _e, _r, _t, _y, _u, _i, _o, _p,
    _a, _s, _d, _f, _g, _h, _j, _k, _l,
    _z, _x, _c, _v, _b, _n, _m,
    _f1, _f2, _f3, _f4, _f5, _f6, _f7, _f8, _f9, _f10, _f11, _f12,
    _enter,
    _c_enter,
    _l_control,
    _l_shift,
    _comma,
    _point,
    _r_shift,
    _prn_scr,
    _l_alt,
    _caps_lock,
    _num_lock,
    _scroll_lock,
    _home,
    _c_home,
    _up,
    _left,
    _right,
    _down,
    _pgup,
    _pgdn,
    _end,
    _ins,
    _del,
    _c_asterisk,
    _c_minus,
    _c_plus,
    _c_1,
    _c_2,
    _c_3,
    _c_4,
    _c_5,
    _c_6,
    _c_8,
    _c_0,
    _c_del,
    _less,
    _equals,
    _greater,
    _asterisk,
    _r_alt,
    _r_control,
    _menu,
    _l_windows,
    _r_windows,
    _close_window,
    _FOO_KEY
};
*/
enum RF_Signal{
    S_AWAKE,
    S_AWAKE_TREE,
    S_KILL,
    S_KILL_TREE,
    S_SLEEP,
    S_SLEEP_TREE,
};
template<typename T>
struct Vector2{
    T x,y;
    Vector2(T x0=0,T y0=0){x=x0; y=y0;}
    Vector2(const Vector2& c){x=c.x; y=c.y;}
};
struct Transform{
    Vector2<float> position, scale;
    float rotation;
};

class RF_Engine;
class RF_Process;
class RF_Window;

//Procesos
/*class mainProcess;
class exeControl;*/

#endif // RF_DECLARES_H
