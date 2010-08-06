/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL_H_
#define MODEL_H_

#include <cassert>
#include <List.h>
#include <Vector.h>
#include <Reflection.h>
#include <Object.h>

#include "painting/Color.h"
//#include "Line.h"
#include "geometry/Geometry.h"
#include "AbstractModel.h"
//#include "Rectangle.h"
//#include ""
//#include ""

#include "ParalaxModel.h"

namespace Model {

//class IModel;
//typedef Core::List <Ptr <IModel> > WidgetList;
//typedef Core::Vector <Ptr <IModel> > WidgetVector;

///// Marker
//struct IModel : public Core::Object {
//        virtual ~IModel () {}
//};

/****************************************************************************/

//// TODO parent. Bez tego nie zadziała
//template <typename Model>
//class ModelHolder {
//public:
//
//        virtual ~ModelHolder () {}
//        void setModel (Ptr <IModel> model);
//
//private:
//
//        Ptr <Model> model;
//
//};

/*--------------------------------------------------------------------------*/

//template <typename Model>
//void ModelHolder<Model>::setModel (Ptr <IModel> model)
//{
//        model = dynamic_pointer_cast <Model> (model);
//        assert (model);
//}

/****************************************************************************/

//class Item : public IModel {
//public:
//
//        __c (void)
//
//        Item () : rotateAngle (0.0), scaleW (1.0), scaleH (1.0), width (0.0), height (0.0) {}
//        virtual ~Item () {}
//
///*--------------------------------------------------------------------------*/
//
//        /* TODO
//         * - absolute transformations:
//         * setPosition
//         * setAngle
//         * setSize
//         *
//         * - relative
//         * setMove
//         * setRotate
//         * setResize
//         */
//
//        virtual void translate (const Geometry::Point &p) { translatePoint += p; }
//        virtual void rotate (double r) { rotateAngle += r; }
//        virtual void scale (double w, double h) { scaleW += w; scaleH += h; }
//
//        virtual Model::Point getTranslatePoint () const { return translatePoint; }
//        _m (setTranslatePoint) virtual void setTranslatePoint (const Model::Point &p) { translatePoint = p; }
//
//        // TODO może raczej rotationAngle
//        virtual double getRotateAngle () const { return rotateAngle; }
//        _m (setRotateAngle) virtual void setRotateAngle (double r) { rotateAngle = r; }
//
//        virtual double getScaleW () const { return scaleW; }
//        virtual double getScaleH () const { return scaleH; }
//        _m (setScale) virtual void setScale (double w, double h) { scaleW = w; scaleH = h; }
//
///*--------------------------------------------------------------------------*/
//
//        _m (setCenter) virtual void setCenter (const Model::Point &p) { center = p; }
//        virtual const Model::Point &getCenter () const { return center; }
//
//        virtual double getHeight () const { return height; }
//        _m (setHeight) virtual void setHeight (double height) { this->height = height; }
//
//        virtual double getWidth () const { return width; }
//        _m (setWidth) virtual void setWidth (double width) { this->width = width; }
//
//private:
//
//        Model::Point center;
//        Model::Point translatePoint;
//        double rotateAngle;
//        double scaleW, scaleH;
//        double width;
//        double height;
//
//        _e (Item)
//};
//
//class Primitive : public Item {
//public:
//        __c (void)
//        _b ("Item")
//
//        Primitive () : lineWidth (0.0) {}
//        virtual ~Primitive () {}
//
//        virtual const Model::Color &getColor() const { return color; }
//        _m (setColor) virtual void setColor (const Model::Color &color) { this->color = color; }
//
//        virtual const Model::Color &getFillColor () const { return fillColor; }
//        _m (setFillColor) virtual void setFillColor (const Model::Color &color) { this->fillColor = color; }
//
//        virtual const Model::LinePattern &getLinePattern() const { return linePattern; }
//        _m (setLinePattern) virtual  void setLinePattern (const Model::LinePattern &linePattern) {  this->linePattern = linePattern; }
//
//        virtual double getLineWidth() const { return lineWidth; }
//        _m (setLineWidth) virtual void setLineWidth(double lineWidth) { this->lineWidth = lineWidth; }
//
//private:
//
//        Model::Color color;
//        Model::Color fillColor;
//
//        Model::LinePattern linePattern;
//        double lineWidth;
//
//        _e (Primitive)
//};

class Image : public Model::Box {
public:
        __c (void)
        _b ("Model::Box")

        virtual ~Image () {}

        virtual Core::String getPath() const { return path; }
        _m (setPath) virtual void setPath (const Core::String &path) { this->path = path; }

private:

        Core::String path;
        _e (Model::Image);
};

///**
// * Set of points with color and tranformations (ie,. you can
// * scale them and rotate etc).
// */
//class PointSet : public Primitive {
//public:
//
//        virtual ~PointSet () {}
//
//        virtual Ptr <Model::PointList> getPoints () const { return points; }
//        virtual void setPoints (Ptr <Model::PointList> p) { points = p; }
//
//private:
//
//        Ptr <Model::PointList> points;
//
//};

} // nam

#	endif /* MODEL_H_ */
