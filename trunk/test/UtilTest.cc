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

/**
 * T musi mieć konstruktor bezargumentowy. W przeciwnym wypadku będzie
 * niezainicjowany (jeśli T będzie wskaźnikiem), lub będzie błąd kompilacji.
 *
 * TODO Zawęzić dla wskaźników jakoś (żeby się nie dało innych typów niż wskaźniki?)
 * TODO Iterator zmienić na ForwardIterator, bo ma tylko operator* const.
 */
template <typename T>
class TreeMaster {
public:

        typedef T Element;
        typedef typename std::vector <T> ElementList;
        typedef typename ElementList::iterator Iterator;
//        typedef typename ElementList::const_iterator ConstIterator;

        TreeMaster () : parent () {}

        Element getParent () { return parent; }
        const Element &getParent () const { return parent; }

        const ElementList &getChildren () const { return children; }
        void setChildren (const ElementList &e) { children = e; }
        void addChild (const Element &e)
        {
                children.push_back (e);
//                e->setParent (*this);
        }
        void removeChild (const Element &e) { children.erase (std::find (children.begin (), children.end (), e)); }
        void clearChildren () { children.clear (); }

//        ConstIterator begin () const { return children.begin (); }
        Iterator begin () { return children.begin (); }
//        ConstIterator end () const { return children.end (); }
        Iterator end () { return children.end (); }

private:

        void setParent (const Element &p) { parent = p; }

private:

        Element parent;
        ElementList children;
};

class Model;

class Controller : public TreeMaster <Ptr <Controller> > {
public:

        Controller (const std::string &n) : name (n) {}

        Ptr <Model> getModel () const { return model; }
//        Ptr <Model> getModel () { return model; }
        void setModel (Ptr <Model> m);

        std::string name;

private:

        Ptr <Model> model;
};


//template <class Class, typename Type, Type (Class::*ptrToMemberFunction) () const>
//struct ConstMemFun
//{
//        typedef typename boost::remove_reference<Type>::type result_type;
//
//        const Type &operator () (const Class& x) const
//        {
//                return (x.*ptrToMemberFunction)();
//        }
//};

//template <typename Class, typename Type, Type (Class::*ptrToMemberFunction) () const>
//struct ConstMemFun
//{
//        typedef typename boost::remove_reference<Type>::type result_type;
//
//        Type operator () (Ptr <Class> const &x) const
//        {
//                return ((*x).*ptrToMemberFunction)();
//        }
//};


template <class Class, typename Type, Type (Class::*ptrToMemberFunction)() const, typename ClassInstanceType = Class>
struct ConstMemFun
{
        typedef typename boost::remove_reference<Type>::type result_type;

        Type operator()(ClassInstanceType const &x) const
        {
                return (x.*ptrToMemberFunction)();
//                return ((*x).*ptrToMemberFunction)();
        }

};

template <class Class, typename Type, Type (Class::*ptrToMemberFunction)(), typename ClassInstanceType>
struct ConstMemFun <Class, Type, ptrToMemberFunction, Ptr <ClassInstanceType> >
{
        typedef typename boost::remove_reference<Type>::type result_type;

        Type operator()(Ptr <ClassInstanceType> const &x) const
        {
                return ((*x).*ptrToMemberFunction)();
        }

};


template <class Class, typename Type,Type (Class::*ptrToMemberFunction)()>
struct MemFun
{
        typedef typename boost::remove_reference<Type>::type result_type;

        Type operator()(Class& x)const
        {
                return (x.*ptrToMemberFunction)();
        }

};


/**
 * Iterator dla TreeSlave.
 */
template <typename T, typename TreeMasterType, typename Extractor>
class TreeSlaveIterator : public std::iterator <std::input_iterator_tag, T> {
public:

        typedef typename TreeMasterType::Iterator TreeMasterIterator;

        TreeSlaveIterator (const TreeMasterIterator &b) : extractor (), body (b) {}
        TreeSlaveIterator(const TreeSlaveIterator &i) : body (i.body) {}

//        const T& operator* () const
        T operator* () const
        {
                return extractor (*body);
        }

        const T* operator-> () const {
                return &(operator* ());
        }

        TreeSlaveIterator&
        operator++()
        {
                body++;
                return *this;
        }

        TreeSlaveIterator
        operator++(int)
        {
                TreeSlaveIterator tmp = *this;
                body++;
                return tmp;
        }

        bool operator== (const TreeSlaveIterator &i) const { return body == i.body; }
        bool operator!= (const TreeSlaveIterator &i) const { return body == i.body; }

private :

        Extractor extractor;
        TreeMasterIterator body;

};






template <typename T, typename TreeMasterType, typename Extractor>
class TreeSlave {
public:

        typedef T Element;
        typedef typename std::list <T> ElementList;
        typedef TreeSlaveIterator <T, TreeMasterType, Extractor> Iterator;
        typedef TreeMasterType * TreeMasterPtr;


        TreeSlave () : treeMaster (NULL) {}

        TreeMasterPtr getTreeMaster () { return treeMaster; }
        void setTreeMaster (TreeMasterPtr t) { treeMaster = t; }

        Element getParent () { return extractor (treeMaster->getParent ()); }

        const ElementList &getChildren () const
        {
                ElementList ret;
                std::for_each (begin (), end (), std::mem_fun (&ElementList::push_back));
                return ret;
        }

        Iterator begin () { return Iterator (treeMaster->begin ()); }
        Iterator end () { return Iterator (treeMaster->end ()); }

private:

        Extractor extractor;
        TreeMasterPtr treeMaster;
};


class Model : public TreeSlave <
                        Ptr <Model>,
                        TreeMaster <Ptr <Controller> >,
                        ConstMemFun <Controller, Ptr <Model>, &Controller::getModel, Ptr <Controller> >
                                > {
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

//        mA->begin ();
        for (Model::Iterator i = mA->begin (); i != mA->end (); ++i) {
                std::cout << (*i)->name << std::endl;
        }

//        std::for_each (mA->begin (), mA->end (), );

//        cA.setModel()


//        ConstMemFun <A, std::string, &A::getBla> functionObject;
//        A a;
//
//        std::string s = functionObject (a);
//        std::cerr << s << std::endl;

//        std::cerr << std::mem_fun (&A::getBla) (&a) << std::endl;
}

BOOST_AUTO_TEST_SUITE_END ();
