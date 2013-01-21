/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IEVENTDISPATHER_H_
#define IEVENTDISPATHER_H_

namespace Model {
struct IModel;
}

namespace View {
class GLContext;
}

namespace Event {
class IEvent;
class PointerInsideIndex;
class EventIndex;

/**
 * Obsługuje eventy wejścia, czyli klawiatura, myszka sensory.
 * - Konwertuje eventy z systemu na eventy bajki.
 * - Rozsyła te eventy do zainteresowanych kontrolerów.
 */
class IEventDispatcher {
public:
        virtual ~IEventDispatcher () {}

        /**
         * @param systemEvent Event z systemu, czyli na przykład z SDL, czy AInputEvent z androida.
         * @param ctx GLContext, który jest potrzebny, zeby zamieniać współrzędne kursora myszy na
         * współrzędne projekcji.
         * @return Zwraca true, gdy event został obsłużony przez jakikolwiek kontroler. Czyli, jeśli
         * kontroler z metody obsługującej ten event zwórócił coś innego niż IGNORED. Jeżeli żaden
         * kontroler nie złapał tego eventu, albo każdy który go złapał zwrócił IGNORED, to metoda
         * zwróci false i w przypadku Androida, event trafi do systemu.
         */
        virtual bool process (void *systemEvent,
                              Model::IModel *model,
                              Event::EventIndex const &modeliIndex,
                              Event::PointerInsideIndex *pointerInsideIndex,
                              View::GLContext const *ctx) = 0;
};

} /* namespace Event */
#endif /* IEVENTDISPATHER_H_ */
