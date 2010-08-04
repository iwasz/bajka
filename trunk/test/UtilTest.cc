#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>

#include "Util.h"

#include <list>
#include <boost/type_traits.hpp>
#include <boost/lambda/lambda.hpp>


BOOST_AUTO_TEST_SUITE (UtilTest);
 
BOOST_AUTO_TEST_CASE (testBasic)
{
        BOOST_CHECK (Util::Math::nextSqr (1) == 1);
        BOOST_CHECK (Util::Math::nextSqr (2) == 2);
        BOOST_CHECK (Util::Math::nextSqr (3) == 4);
        BOOST_CHECK (Util::Math::nextSqr (5) == 8);
        BOOST_CHECK (Util::Math::nextSqr (9) == 16);
        BOOST_CHECK (Util::Math::nextSqr (1000) == 1024);
        BOOST_CHECK (Util::Math::nextSqr (1024) == 1024);
}


class Model;

class Controller : public Util::TreeMaster <Controller> {
public:

        Controller (const std::string &n) : name (n) {}

        Ptr <Model> getModel () const { return model; }
        void setModel (Ptr <Model> m);

        std::string name;

private:

        Ptr <Model> model;
};


class Model : public Util::TreeSlave <Model,
                                Controller,
                                &Controller::getModel> {

public:

        Model (const std::string &n) : name (n) {}
        std::string name;

};


void Controller::setModel (Ptr <Model> m)
{
        model = m;
        model->setTreeMaster (this);
}


BOOST_AUTO_TEST_CASE (testTree)
{
        typedef Ptr <Controller> CtrPtr;
        typedef Ptr <Model> MdlPtr;

        CtrPtr cA = CtrPtr (new Controller ("cA"));
        CtrPtr cB = CtrPtr (new Controller ("cB"));
        CtrPtr cC = CtrPtr (new Controller ("cC"));
        CtrPtr cD = CtrPtr (new Controller ("cD"));
        CtrPtr cE = CtrPtr (new Controller ("cE"));

        MdlPtr mA = MdlPtr (new Model ("mA"));
        MdlPtr mB = MdlPtr (new Model ("mB"));
        MdlPtr mC = MdlPtr (new Model ("mC"));
        MdlPtr mD = MdlPtr (new Model ("mD"));
        MdlPtr mE = MdlPtr (new Model ("mE"));

        cA->setModel (mA);
        cB->setModel (mB);
        cC->setModel (mC);
        cD->setModel (mD);
        cE->setModel (mE);

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

        Controller::Iterator i = cA->begin ();
        BOOST_CHECK ((*i)->name == "cB");
        BOOST_CHECK ((*i)->getParent () == cA.get ());
        ++i;
        BOOST_CHECK ((*i)->name == "cC");
        BOOST_CHECK ((*i)->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK ((*i)->name == "cD");
        BOOST_CHECK ((*i)->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK ((*i)->name == "cE");
        BOOST_CHECK ((*i)->getParent () == cC.get ());

        Model::Iterator j = mA->begin ();
        BOOST_CHECK ((*j)->name == "mB");
        BOOST_CHECK ((*j)->getParent () == mA);
        ++j;
        BOOST_CHECK ((*j)->name == "mC");
        BOOST_CHECK ((*j)->getParent () == mA);

        j = mB->begin ();
        BOOST_CHECK ((*j)->name == "mD");
        BOOST_CHECK ((*j)->getParent () == mB);

        j = mC->begin ();
        BOOST_CHECK ((*j)->name == "mE");
        BOOST_CHECK ((*j)->getParent () == mC);
}


BOOST_AUTO_TEST_SUITE_END ();
