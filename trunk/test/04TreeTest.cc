#include <boost/test/unit_test.hpp>
#include <sstream>
#include <Pointer.h>
#include <string>
#include <iostream>

#include "tree/Tree.h"
#include "helpers/T_AbstractController.h"
#include "helpers/T_AbstractModel.h"
#include "helpers/T_AbstractWidget.h"

using namespace Controller;
using namespace View;
using namespace Model;

/*--------------------------------------------------------------------------*/

// Lista dzieci jest jako IController, więc potrzebny kast
std::string getNameCtr (Ptr <IController> const &i)
{
        return dynamic_pointer_cast <T_AbstractController> (i)->getName ();
}

std::string getNameCtr (IController *i)
{
        return dynamic_cast <T_AbstractController *> (i)->getName ();
}

std::string getNameWgt (Ptr <IWidget> const &i)
{
        return dynamic_pointer_cast <T_AbstractWidget> (i)->getName ();
}

std::string getNameWgt (IWidget *i)
{
        return dynamic_cast <T_AbstractWidget *> (i)->getName ();
}

std::string getNameMdl (Ptr <IModel> const &i)
{
        return dynamic_pointer_cast <T_AbstractModel> (i)->getName ();
}

std::string getNameMdl (IModel *i)
{
        return dynamic_cast <T_AbstractModel *> (i)->getName ();
}

/*--------------------------------------------------------------------------*/

BOOST_AUTO_TEST_CASE (InstantiationTest)
{
     T_AbstractController c ("");

     Ptr <T_AbstractModel> m = Ptr <T_AbstractModel> (new T_AbstractModel (""));
     c.setModel (m);

     Ptr <T_AbstractWidget> w = Ptr <T_AbstractWidget> (new T_AbstractWidget (""));
     c.setWidget (w);

     c.getName ();
}

/**
 * Prosty parent test, przy czym kontroler dostaje tylko model. Nie ustawiam
 * widgetów.
 *
 * Tworzę strukturę drzewiastą kontrolerów, z których kazdy ma ustawiony model,
 * ale nie ma ustawionego widgetu. Sprawdzam, czy kontrolery zwracają poprawnie
 * dzieci i czy modle poprawnie zwracają child-modele.
 */
BOOST_AUTO_TEST_CASE (ParentTestM_C)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;

        CtrPtr cA = CtrPtr (new T_AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new T_AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new T_AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new T_AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new T_AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        cA->setModel (mA);
        cB->setModel (mB);
        cC->setModel (mC);
        cD->setModel (mD);
        cE->setModel (mE);

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

        T_AbstractController::iterator i = cA->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cB");
        BOOST_CHECK ((*i)->getParent () == cA.get ());
        ++i;
        BOOST_CHECK (getNameCtr (*i) == "cC");
        BOOST_CHECK ((*i)->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cD");
        BOOST_CHECK ((*i)->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cE");
        BOOST_CHECK ((*i)->getParent () == cC.get ());

        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        ++j;
        BOOST_CHECK (getNameMdl (*j) == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());
}

/**
 * Tu tworzę kontrolery, ktopre mają widgety i modele a następnie zagnieżdżam
 * jedne kontrolery w drugich.
 *
 * Tworzę strukturę drzewiastą kontrolerów, z których kazdy ma ustawiony model,
 * i ustawiony widget. Sprawdzam, czy kontrolery zwracają poprawnie dzieci, modle
 * poprawnie zwracają child-modele, a widgety child widgety.
 */
BOOST_AUTO_TEST_CASE (ParentTestM_V_C)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        CtrPtr cA = CtrPtr (new T_AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new T_AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new T_AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new T_AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new T_AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

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
        T_AbstractController::iterator i = cA->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cB");
        BOOST_CHECK ((*i)->getParent () == cA.get ());
        ++i;
        BOOST_CHECK (getNameCtr (*i) == "cC");
        BOOST_CHECK ((*i)->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cD");
        BOOST_CHECK ((*i)->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cE");
        BOOST_CHECK ((*i)->getParent () == cC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());
        ++j;
        BOOST_CHECK (getNameMdl (*j) == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia widgetów.
        T_AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wB");
        BOOST_CHECK ((*k)->getParent () == wA.get ());
        ++k;
        BOOST_CHECK (getNameWgt (*k) == "wC");
        BOOST_CHECK ((*k)->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wD");
        BOOST_CHECK ((*k)->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wE");
        BOOST_CHECK ((*k)->getParent () == wC.get ());
}

/**
 * Test sprawdza strukturę drzewiastą widgetów. Każdy widget ma podpięty
 * jakiś model. następnie sprawdzam, czy widgety poprawnie zwracają swoje
 * dzieci (w postaci widgetów), a modele dzieci w postaci modeli.
 */
BOOST_AUTO_TEST_CASE (WidgetParentTest)
{
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

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
        T_AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wB");
        BOOST_CHECK ((*k)->getParent () == wA.get ());
        ++k;
        BOOST_CHECK (getNameWgt (*k) == "wC");
        BOOST_CHECK ((*k)->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wD");
        BOOST_CHECK ((*k)->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wE");
        BOOST_CHECK ((*k)->getParent () == wC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());
        ++j;
        BOOST_CHECK (getNameMdl (*j) == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());
}

/**
 * Tu tworzę kontrolery, ktopre mają widgety i modele a następnie zagnieżdżam
 * jedne kontrolery w drugich. Potem czyszczę dzieci i sprawdzam, czy wyzerowały
 * się wskaźniki do rodziców.
 */
BOOST_AUTO_TEST_CASE (clearChildrenTest)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        CtrPtr cA = CtrPtr (new T_AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new T_AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new T_AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new T_AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new T_AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

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

        BOOST_CHECK (!cA->hasChildren ());
        BOOST_CHECK (!cB->hasChildren ());
        BOOST_CHECK (!cC->hasChildren ());
        BOOST_CHECK (!cD->hasChildren ());
        BOOST_CHECK (!cE->hasChildren ());

        BOOST_CHECK (!mA->hasChildren ());
        BOOST_CHECK (!mB->hasChildren ());
        BOOST_CHECK (!mC->hasChildren ());
        BOOST_CHECK (!mD->hasChildren ());
        BOOST_CHECK (!mE->hasChildren ());

        BOOST_CHECK (!wA->hasChildren ());
        BOOST_CHECK (!wB->hasChildren ());
        BOOST_CHECK (!wC->hasChildren ());
        BOOST_CHECK (!wD->hasChildren ());
        BOOST_CHECK (!wE->hasChildren ());
}

/**
 * Testuje działanie metody hasChildren.
 */
BOOST_AUTO_TEST_CASE (hasChildren)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        CtrPtr cA = CtrPtr (new T_AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new T_AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new T_AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new T_AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new T_AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

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

        BOOST_CHECK (cA->hasChildren ());
        BOOST_CHECK (cB->hasChildren ());
        BOOST_CHECK (cC->hasChildren ());
        // LIŚCIE Te już nie mają dzieci.
        BOOST_CHECK (!cD->hasChildren ());
        BOOST_CHECK (!cE->hasChildren ());

        BOOST_CHECK (mA->hasChildren ());
        BOOST_CHECK (mB->hasChildren ());
        BOOST_CHECK (mC->hasChildren ());
        // LIŚCIE Te już nie mają dzieci.
        BOOST_CHECK (!mD->hasChildren ());
        BOOST_CHECK (!mE->hasChildren ());

        BOOST_CHECK (wA->hasChildren ());
        BOOST_CHECK (wB->hasChildren ());
        BOOST_CHECK (wC->hasChildren ());
        // LIŚCIE Te już nie mają dzieci.
        BOOST_CHECK (!wD->hasChildren ());
        BOOST_CHECK (!wE->hasChildren ());
}

/*##########################################################################*/
/*
 * TESTY z odwróconą kolejnością setterów - najpierw zagneżdżanie, a potem
 * ustawione modele i widgety
 */
/*##########################################################################*/

/**
 * Prosty parent ntest, przy czym kontroler dostaje tylko model. Nie ustawiam
 * widgetów.
 */
BOOST_AUTO_TEST_CASE (ParentTestM_C_Order)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;

        CtrPtr cA = CtrPtr (new T_AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new T_AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new T_AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new T_AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new T_AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

        cA->setModel (mA);
        cB->setModel (mB);
        cC->setModel (mC);
        cD->setModel (mD);
        cE->setModel (mE);

        T_AbstractController::iterator i = cA->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cB");
        BOOST_CHECK ((*i)->getParent () == cA.get ());
        ++i;
        BOOST_CHECK (getNameCtr (*i) == "cC");
        BOOST_CHECK ((*i)->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cD");
        BOOST_CHECK ((*i)->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cE");
        BOOST_CHECK ((*i)->getParent () == cC.get ());

        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        ++j;
        BOOST_CHECK (getNameMdl (*j) == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());
}

/**
 * Tu tworzę kontrolery, ktopre mają widgety i modele a następnie zagnieżdżam
 * jedne kontrolery w drugich.
 */
BOOST_AUTO_TEST_CASE (ParentTestM_V_C_Order)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        CtrPtr cA = CtrPtr (new T_AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new T_AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new T_AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new T_AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new T_AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

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

        // Tu sprawdzam strukturę zagnieżdżenia kontrolerów.
        T_AbstractController::iterator i = cA->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cB");
        BOOST_CHECK ((*i)->getParent () == cA.get ());
        ++i;
        BOOST_CHECK (getNameCtr (*i) == "cC");
        BOOST_CHECK ((*i)->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cD");
        BOOST_CHECK ((*i)->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK (getNameCtr (*i) == "cE");
        BOOST_CHECK ((*i)->getParent () == cC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());
        ++j;
        BOOST_CHECK (getNameMdl (*j) == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia widgetów.
        T_AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wB");
        BOOST_CHECK ((*k)->getParent () == wA.get ());
        ++k;
        BOOST_CHECK (getNameWgt (*k) == "wC");
        BOOST_CHECK ((*k)->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wD");
        BOOST_CHECK ((*k)->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wE");
        BOOST_CHECK ((*k)->getParent () == wC.get ());
}

/**
 * zagnieżdżanie widgetów, ale odwrócona kolejność. Najpierw jest tworzona
 * struktura drzewiasta widgetów a dopiero potem podpinane są modele. Dalej
 * wykonuję standardowe sprawdzenia iteratorów od dzieci.
 *
 * Ten test jest stworzony, ponieważ wcześniejsza implementacja, gdzie modele
 * miały wewnętrznie kolekcję dzieci, która była uaktualniana przez kontroler
 * nie działała przy powyższym scenariuszu.
 */
BOOST_AUTO_TEST_CASE (WidgetParentTest_Order)
{
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

        wA->addChild (wB);
        wA->addChild (wC);
        wB->addChild (wD);
        wC->addChild (wE);

        wA->setModel (mA);
        wB->setModel (mB);
        wC->setModel (mC);
        wD->setModel (mD);
        wE->setModel (mE);

        // Tu sprawdzam strukturę zagnieżdżenia widgetów.
        T_AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wB");
        BOOST_CHECK ((*k)->getParent () == wA.get ());
        ++k;
        BOOST_CHECK (getNameWgt (*k) == "wC");
        BOOST_CHECK ((*k)->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wD");
        BOOST_CHECK ((*k)->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK (getNameWgt (*k) == "wE");
        BOOST_CHECK ((*k)->getParent () == wC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mB");
        BOOST_CHECK ((*j)->getParent () == mA.get ());
        ++j;
        BOOST_CHECK (getNameMdl (*j) == "mC");
        BOOST_CHECK ((*j)->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mD");
        BOOST_CHECK ((*j)->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (*j) == "mE");
        BOOST_CHECK ((*j)->getParent () == mC.get ());
}

/**
 * test sprawdzający działanie getParent w TreeMasterSlave, a konkretnie
 * czy nie występuje jeden konkrety BUG, który znalazłem. Kiedy nie było
 * ustawionego parenta, TreeMasterSlave::getParent próbowało wykonać
 * getParent ownera, ale nie sprawdzało czy owner jest ustawiony:
 */
BOOST_AUTO_TEST_CASE (WidgetParentBUG)
{
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));

        /*
         * Tu się wywalało. To że parent jest null, nie oznacza, ze trzeba szukać
         * w owner, bo równie dobrze może oznaczac, że jesteśmy korzeniem, który
         * nie ma rodzica.
         */
        BOOST_CHECK (!wA->getParent ());

        wA->setModel (mA);

        BOOST_CHECK (!wA->getParent ());
}

/*##########################################################################*/
/*
 * Testy iteratorów.
 */
/*##########################################################################*/

/**
 * Testujemy operator -> iteratora TreeIter.
 */
BOOST_AUTO_TEST_CASE (TreeIterTest)
{
        typedef Ptr <IController> CtrPtr;
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        CtrPtr cA = CtrPtr (new T_AbstractController ("cA"));
        CtrPtr cB = CtrPtr (new T_AbstractController ("cB"));
        CtrPtr cC = CtrPtr (new T_AbstractController ("cC"));
        CtrPtr cD = CtrPtr (new T_AbstractController ("cD"));
        CtrPtr cE = CtrPtr (new T_AbstractController ("cE"));

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

        cA->addChild (cB);
        cA->addChild (cC);
        cB->addChild (cD);
        cC->addChild (cE);

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

        // Tu sprawdzam strukturę zagnieżdżenia kontrolerów.
        T_AbstractController::iterator i = cA->begin ();
        /*
         * i-> zwraca wskaźnik do Ptr <IController>. Na nim wywołujemy metodę get() (ona zwraca
         * IController *, a na tym wykonujemy metodę getName ().
         */
        BOOST_CHECK (getNameCtr (i->get()) == "cB");
        BOOST_CHECK (i->get()->getParent () == cA.get ());
        ++i;
        BOOST_CHECK (getNameCtr (i->get()) == "cC");
        BOOST_CHECK (i->get()->getParent () == cA.get ());

        i = cB->begin ();
        BOOST_CHECK (getNameCtr (i->get()) == "cD");
        BOOST_CHECK (i->get()->getParent () == cB.get ());

        i = cC->begin ();
        BOOST_CHECK (getNameCtr (i->get()) == "cE");
        BOOST_CHECK (i->get()->getParent () == cC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (j->get()) == "mB");
        BOOST_CHECK (j->get()->getParent () == mA.get ());
        ++j;
        BOOST_CHECK (getNameMdl (j->get()) == "mC");
        BOOST_CHECK (j->get()->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (j->get()) == "mD");
        BOOST_CHECK (j->get()->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (j->get()) == "mE");
        BOOST_CHECK (j->get()->getParent () == mC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia widgetów.
        T_AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK (getNameWgt (k->get()) == "wB");
        BOOST_CHECK (k->get()->getParent () == wA.get ());
        ++k;
        BOOST_CHECK (getNameWgt (k->get()) == "wC");
        BOOST_CHECK (k->get()->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK (getNameWgt (k->get()) == "wD");
        BOOST_CHECK (k->get()->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK (getNameWgt (k->get()) == "wE");
        BOOST_CHECK (k->get()->getParent () == wC.get ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (WidgetParentTest_TreeIterTest)
{
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

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
        T_AbstractWidget::iterator k = wA->begin ();
        BOOST_CHECK (getNameWgt (k->get()) == "wB");
        BOOST_CHECK (k->get()->getParent () == wA.get ());
        ++k;
        BOOST_CHECK (getNameWgt (k->get()) == "wC");
        BOOST_CHECK (k->get()->getParent () == wA.get ());

        k = wB->begin ();
        BOOST_CHECK (getNameWgt (k->get()) == "wD");
        BOOST_CHECK (k->get()->getParent () == wB.get ());

        k = wC->begin ();
        BOOST_CHECK (getNameWgt (k->get()) == "wE");
        BOOST_CHECK (k->get()->getParent () == wC.get ());

        // Tu sprawdzam strukturę zagnieżdżenia modeli.
        T_AbstractModel::iterator j = mA->begin ();
        BOOST_CHECK (getNameMdl (j->get()) == "mB");
        BOOST_CHECK (j->get()->getParent () == mA.get ());
        ++j;
        BOOST_CHECK (getNameMdl (j->get()) == "mC");
        BOOST_CHECK (j->get()->getParent () == mA.get ());

        j = mB->begin ();
        BOOST_CHECK (getNameMdl (j->get()) == "mD");
        BOOST_CHECK (j->get()->getParent () == mB.get ());

        j = mC->begin ();
        BOOST_CHECK (getNameMdl (j->get()) == "mE");
        BOOST_CHECK (j->get()->getParent () == mC.get ());
}

/**
 * Test sprawdza, czy iteratory po skopiowaniu są niezależne od siebie.
 * To może nie działać, bo TreeIter zawiera w sobie wskaźnik do polimorficznej
 * implementacji.
 */
BOOST_AUTO_TEST_CASE (TreeIter_copy)
{
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

        wA->setModel (mA);
        wB->setModel (mB);
        wC->setModel (mC);
        wD->setModel (mD);
        wE->setModel (mE);

        wA->addChild (wB);
        wA->addChild (wC);
        wB->addChild (wD);
        wC->addChild (wE);

        T_AbstractWidget::iterator k = wA->begin ();
        T_AbstractWidget::iterator l = k;

        BOOST_CHECK (getNameWgt (k->get()) == "wB");
        BOOST_CHECK (getNameWgt (l->get()) == "wB");

        ++k;

        BOOST_CHECK (getNameWgt (k->get()) == "wC");
        BOOST_CHECK (getNameWgt (l->get()) == "wB");

        {
                T_AbstractWidget::iterator k = wA->begin ();
                T_AbstractWidget::iterator l (k);

                BOOST_CHECK (getNameWgt (k->get()) == "wB");
                BOOST_CHECK (getNameWgt (l->get()) == "wB");

                ++k;

                BOOST_CHECK (getNameWgt (k->get()) == "wC");
                BOOST_CHECK (getNameWgt (l->get()) == "wB");
        }

        {
                T_AbstractWidget::iterator k = wA->begin ();
                T_AbstractWidget::iterator l;
                l = k;

                BOOST_CHECK (getNameWgt (k->get()) == "wB");
                BOOST_CHECK (getNameWgt (l->get()) == "wB");

                ++k;

                BOOST_CHECK (getNameWgt (k->get()) == "wC");
                BOOST_CHECK (getNameWgt (l->get()) == "wB");
        }
}

BOOST_AUTO_TEST_CASE (TreeIter_empty)
{
        typedef Ptr <IModel> MdlPtr;
        typedef Ptr <IWidget> WdgPtr;

        MdlPtr mA = MdlPtr (new T_AbstractModel ("mA"));
        MdlPtr mB = MdlPtr (new T_AbstractModel ("mB"));
        MdlPtr mC = MdlPtr (new T_AbstractModel ("mC"));
        MdlPtr mD = MdlPtr (new T_AbstractModel ("mD"));
        MdlPtr mE = MdlPtr (new T_AbstractModel ("mE"));

        WdgPtr wA = WdgPtr (new T_AbstractWidget ("wA"));
        WdgPtr wB = WdgPtr (new T_AbstractWidget ("wB"));
        WdgPtr wC = WdgPtr (new T_AbstractWidget ("wC"));
        WdgPtr wD = WdgPtr (new T_AbstractWidget ("wD"));
        WdgPtr wE = WdgPtr (new T_AbstractWidget ("wE"));

        wA->setModel (mA);
        wB->setModel (mB);
        wC->setModel (mC);
        wD->setModel (mD);
        wE->setModel (mE);

        wA->addChild (wB);
        wA->addChild (wC);
        wB->addChild (wD);
        wC->addChild (wE);

        T_AbstractWidget::iterator k = wA->begin ();
        T_AbstractModel::iterator j = mA->begin ();

        T_AbstractWidget::iterator k1, k2;
        T_AbstractModel::iterator j1, j2;

        BOOST_CHECK (k != k1);
        BOOST_CHECK (j != j1);

        BOOST_CHECK (j1 == j2);
        BOOST_CHECK (k1 == k2);

        k = wA->end ();
        j = mA->end ();

        BOOST_CHECK (k != k1);
        BOOST_CHECK (j != j1);
}

