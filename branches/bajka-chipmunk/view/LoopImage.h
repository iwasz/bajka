/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_LOOPIMAGE_H_
#define BAJKA_LOOPIMAGE_H_

namespace View {

class LoopImage : public Image {
public:
        C__ (void)
        b_ ("Image")

        virtual ~LoopImage () {}
        virtual void update (Model::IModel *model);

                       Geometry::Point const &getOffset () const { return offset; }
        m_ (setOffset) void setOffset (Geometry::Point const &o) { offset = o; }

protected:

        void drawTile (double x, double y);

private:

        Geometry::Point offset;
        E_ (Image)
};

} /* namespace View */

#	endif /* LOOPIMAGE_H_ */
