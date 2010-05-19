///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#ifndef TYPETAGS_H_
//#define TYPETAGS_H_
//
//namespace Event {
//
///**
// * Zwracanie tych tagów jest zrobione w ten sposób, żeby dało się wszystkie
// * numerki zebrać w jednym pliku, mimo, że definicje eventów są w różnych
// * plikach. Dzięki temu numerki nie będą się dublować.
// */
//template <typename EventType>
//struct TypeTag {
//
//};
//
//#define BAJKA_EVENT_TYPE_TAG(event, number)             \
//template <>                                             \
//struct TypeTag <event> {                                \
//        enum { type = 0x01 << number };                 \
//};
//
//
//BAJKA_EVENT_TYPE_TAG (MouseButtonEvent, 0);
//BAJKA_EVENT_TYPE_TAG (MouseMotionEvent, 1);
//BAJKA_EVENT_TYPE_TAG (KeyboardEvent, 2);
//BAJKA_EVENT_TYPE_TAG (TimerEvent, 3);
//
//} // nam
//
//#	endif /* TYPETAGS_H_ */
