/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EXTRACTORS_H_
#define EXTRACTORS_H_

namespace Util {

//template <typename Class,
//          typename ReturnType,
//          ReturnType (Class::*ptrToMemberFunction)() const,
//          typename ChildInstanceType,
//          typename ParentInstanceType = ChildInstanceType>
//struct ConstMemFunExtractor
//{
//        typedef typename boost::remove_reference<ReturnType>::type result_type;
//
//        ReturnType operator()(ChildInstanceType const &x) const
//        {
//                return (x.*ptrToMemberFunction)();
//        }
//
//        ReturnType operator()(ParentInstanceType const &x) const
//        {
//                return (x.*ptrToMemberFunction)();
//        }
//};

template <typename SlaveElement,
        typename MasterElement,
        Ptr <SlaveElement> (MasterElement::*ptrToMemberFunction)() const>

struct ConstMemFunExtractor
{
        typedef typename boost::remove_reference<SlaveElement>::type result_type;

        /**
         * Uruchamia zadaną metodę i zwraca wynik typu Type.
         * @param x
         * @return
         */
        Ptr <SlaveElement> operator()(Ptr <MasterElement> const &x) const
        {
                if (!x) {
                        return Ptr <SlaveElement> ();
                }

                return ((*x).*ptrToMemberFunction)();
        }

        Ptr <SlaveElement> operator()(MasterElement* const &x) const
        {
                if (!x) {
                        return Ptr <SlaveElement> ();
                }

                return ((*x).*ptrToMemberFunction)();
        }
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

//template <typename Class,
//          typename ReturnType,
//          ReturnType (Class::*ptrToMemberFunction)() const,
//          typename ClassInstanceType>
//
//ConstMemFun <Class, ReturnType, ptrToMemberFunction, ClassInstanceType>
//
//createConstMemFun (ReturnType (Class::*p)() const)
//{
//        return ConstMemFun <Class, ReturnType, p, ClassInstanceType> ();
//}

} // namespace Util

#	endif /* EXTRACTORS_H_ */
