#include <boost/test/unit_test.hpp>
#include <sstream>
#include <Pointer.h>
#include <string>
#include <iostream>

#include "tree/Tree.h"
#include "helpers/AbstractController.h"
#include "helpers/AbstractModel.h"
#include "helpers/AbstractWidget.h"

/**
 * Testuje tylko czy da się stworzyć obiekty podanych klas.
 */
BOOST_AUTO_TEST_CASE (InstantiationTest)
{
     AbstractController c ("");

     Ptr <AbstractModel> m = Ptr <AbstractModel> (new AbstractModel (""));
     c.setModel (m);

     Ptr <AbstractWidget> w = Ptr <AbstractWidget> (new AbstractWidget (""));
     c.setWidget (w);

     c.getName ();
}

/**
 * Prosty parent ntest, przy czym kontroler dostaje tylko model. Nie ustawiam
 * widgetów.
 */
BOOST_AUTO_TEST_CASE (ParentTestM_C)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;

        CtrPtr cA = CtrPtr (new AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new AbstractModel ("mE"));

        cA->setModel (mA);
        cB->setModel (mB);
        cC->setModel (mC);
        cD->setModel (mD);
        cE->setModel (mE);

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

        AbstractController::iterator i = cA->begin ();
        BOOST_CHECK ((*i)->getName () == "cB");
        BOOST_CHECK ((*i)->getParent () == cA.get ());
        ++i;
        BOOST_CHECK ((*i)->getName () == "cC");
        BOOST_CHECK ((*i)->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK ((*i)->getName () == "cD");
        BOOST_CHECK ((*i)->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK ((*i)->getName () == "cE");
        BOOST_CHECK ((*i)->getParent () == cC.get ());

        AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK ((*j)->getName () == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());
        ++j;
        BOOST_CHECK ((*j)->getName () == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK ((*j)->getName () == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK ((*j)->getName () == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());
}

/**
 * Tu tworzę kontrolery, ktopre mają widgety i modele a następnie zagnieżdżam
 * jedne kontrolery w drugich.
 */
BOOST_AUTO_TEST_CASE (ParentTestM_V_C)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        CtrPtr cA = CtrPtr (new AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new AbstractWidget ("wE"));

        cA->setModel (mA);
        cB->setModel (mB);
        cC->setModel (mC);
        cD->setModel (mD);
        cE->setModel (mE);

        cA->setWidget (wA);
        cB->setWidget (wB);
        cC->setWidget (wC);
        cD->setWidget (wD);
        cE->setWidget (wE);

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

        // Tu sprawdzam strukturę zagnieżdżenia kontrolerów.
        AbstractController::iterator i = cA->begin ();
        BOOST_CHECK ((*i)->getName () == "cB");
        BOOST_CHECK ((*i)->getParent () == cA.get ());
        ++i;
        BOOST_CHECK ((*i)->getName () == "cC");
        BOOST_CHECK ((*i)->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK ((*i)->getName () == "cD");
        BOOST_CHECK ((*i)->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK ((*i)->getName () == "cE");
        BOOST_CHECK ((*i)->getParent () == cC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK ((*j)->getName () == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());
        ++j;
        BOOST_CHECK ((*j)->getName () == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK ((*j)->getName () == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK ((*j)->getName () == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia widgetów.
        AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK ((*k)->getName () == "wB");
        BOOST_CHECK ((*k)->getParent () == wA.get ());
        ++k;
        BOOST_CHECK ((*k)->getName () == "wC");
        BOOST_CHECK ((*k)->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK ((*k)->getName () == "wD");
        BOOST_CHECK ((*k)->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK ((*k)->getName () == "wE");
        BOOST_CHECK ((*k)->getParent () == wC.get ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (WidgetParentTest)
{
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        MdlPtr mA = MdlPtr (new AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new AbstractWidget ("wE"));

        wA->setModel (mA);
        wB->setModel (mB);
        wC->setModel (mC);
        wD->setModel (mD);
        wE->setModel (mE);

        wA->addChild (wB);
        wA->addChild (wC);
        wB->addChild (wD);
        wC->addChild (wE);

        // Tu sprawdzam strukturę zagnieżdżenia widgetów.
        AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK ((*k)->getName () == "wB");
        BOOST_CHECK ((*k)->getParent () == wA.get ());
        ++k;
        BOOST_CHECK ((*k)->getName () == "wC");
        BOOST_CHECK ((*k)->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK ((*k)->getName () == "wD");
        BOOST_CHECK ((*k)->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK ((*k)->getName () == "wE");
        BOOST_CHECK ((*k)->getParent () == wC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK ((*j)->getName () == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());
        ++j;
        BOOST_CHECK ((*j)->getName () == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK ((*j)->getName () == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK ((*j)->getName () == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());
}

/**
 * Tu tworzę kontrolery, ktopre mają widgety i modele a następnie zagnieżdżam
 * jedne kontrolery w drugich.
 */
BOOST_AUTO_TEST_CASE (clearChildrenTest)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        CtrPtr cA = CtrPtr (new AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new AbstractWidget ("wE"));

        cA->setModel (mA);
        cB->setModel (mB);
        cC->setModel (mC);
        cD->setModel (mD);
        cE->setModel (mE);

        cA->setWidget (wA);
        cB->setWidget (wB);
        cC->setWidget (wC);
        cD->setWidget (wD);
        cE->setWidget (wE);

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

        cA->clearChildren ();
        cB->clearChildren ();
        cC->clearChildren ();

        BOOST_CHECK (!cA->getParent ());
        BOOST_CHECK (!cB->getParent ());
        BOOST_CHECK (!cC->getParent ());
        BOOST_CHECK (!cD->getParent ());
        BOOST_CHECK (!cE->getParent ());

        BOOST_CHECK (!mA->getParent ());
        BOOST_CHECK (!mB->getParent ());
        BOOST_CHECK (!mC->getParent ());
        BOOST_CHECK (!mD->getParent ());
        BOOST_CHECK (!mE->getParent ());

        BOOST_CHECK (!wA->getParent ());
        BOOST_CHECK (!wB->getParent ());
        BOOST_CHECK (!wC->getParent ());
        BOOST_CHECK (!wD->getParent ());
        BOOST_CHECK (!wE->getParent ());

        BOOST_CHECK (cA->getChildren ().empty ());
        BOOST_CHECK (cB->getChildren ().empty ());
        BOOST_CHECK (cC->getChildren ().empty ());
        BOOST_CHECK (cD->getChildren ().empty ());
        BOOST_CHECK (cE->getChildren ().empty ());

        BOOST_CHECK (mA->getChildren ().empty ());
        BOOST_CHECK (mB->getChildren ().empty ());
        BOOST_CHECK (mC->getChildren ().empty ());
        BOOST_CHECK (mD->getChildren ().empty ());
        BOOST_CHECK (mE->getChildren ().empty ());

        BOOST_CHECK (wA->getChildren ().empty ());
        BOOST_CHECK (wB->getChildren ().empty ());
        BOOST_CHECK (wC->getChildren ().empty ());
        BOOST_CHECK (wD->getChildren ().empty ());
        BOOST_CHECK (wE->getChildren ().empty ());
}
