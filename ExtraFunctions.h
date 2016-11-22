#ifndef _EXTRAFUNCTIONS_H_
#define _EXTRAFUNCTIONS_H_

template <class T> const T& limit (const T& val, const T& min, const T& max){
    return (val < min) ? min : ((val > max) ? max : val);
}
#endif
