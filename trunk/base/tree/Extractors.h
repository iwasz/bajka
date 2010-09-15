/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EXTRACTORS_H_
#define EXTRACTORS_H_

namespace Model {
class IModel;
}

namespace View {
class IWidget;
}

namespace Base {

/**
 * Klasa pobierająca model z o. Jest to klasa pomocnicza używana w TreeIteratorach.
 * Ponieważ TreeIterator zawiera iterator STL (na przykład do kolekcji kontrolerów),
 * jest potrzebne coś, co z tego kontrolera wyciągnie na przykład model lub widget.
 * To jest właśnie zadanie ekstraktora. Jest on funktorem.
 * \inplace Util
 */
struct ModelExtractor {
        // T to może być wskaźnik lub smart_pointer
        template <typename T>
        Model::IModel *operator() (T o) const
        {
                if (!o) {
                        return NULL;
                }

                return o->getModel ().get ();
        }
};

/**
 * Klasa pobierająca model z o. Jest to klasa pomocnicza używana w TreeIteratorach.
 * Ponieważ TreeIterator zawiera iterator STL (na przykład do kolekcji kontrolerów),
 * jest potrzebne coś, co z tego kontrolera wyciągnie na przykład model lub widget.
 * To jest właśnie zadanie ekstraktora. Jest on funktorem.
 * \inplace Util
 */
struct ModelPtrExtractor {
        // T to może być wskaźnik lub smart_pointer
        template <typename T>
        Ptr <Model::IModel> const &operator() (T o) const
        {
                if (!o) {
                        static const Ptr <Model::IModel> tmp;
                        return tmp;
                }

                return o->getModel ();
        }
};

/**
 * Klasa pobierająca widget z o. Jest to klasa pomocnicza używana w TreeIteratorach.
 * Ponieważ TreeIterator zawiera iterator STL (na przykład do kolekcji kontrolerów),
 * jest potrzebne coś, co z tego kontrolera wyciągnie na przykład model lub widget.
 * To jest właśnie zadanie ekstraktora. Jest on funktorem.
 * \inplace Util
 */
struct WidgetExtractor {
        // T to może być wskaźnik lub smart_pointer
        template <typename T>
        View::IWidget *operator() (T o) const
        {
                if (!o) {
                        return NULL;
                }

                return o->getWidget ().get ();
        }
};

/**
 * Klasa pobierająca widget z o. Jest to klasa pomocnicza używana w TreeIteratorach.
 * Ponieważ TreeIterator zawiera iterator STL (na przykład do kolekcji kontrolerów),
 * jest potrzebne coś, co z tego kontrolera wyciągnie na przykład model lub widget.
 * To jest właśnie zadanie ekstraktora. Jest on funktorem.
 * \inplace Util
 */
struct WidgetPtrExtractor {
        // T to może być wskaźnik lub smart_pointer
        template <typename T>
        Ptr <View::IWidget> const &operator() (T o) const
        {
                if (!o) {
                        static const Ptr <View::IWidget> tmp;
                        return tmp;
                }

                return o->getWidget ();
        }
};

/**
 * Dummy extractor, który zwraca swój argument w niezmienionej postaci.
 * \inplace Util
 */
struct NoopExtractor {

        template <typename T>
        T &operator() (T &o) const
        {
                return o;
        }
};

} // namespace

#	endif /* EXTRACTORS_H_ */
