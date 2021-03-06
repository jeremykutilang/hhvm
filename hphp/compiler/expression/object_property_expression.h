/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-present Facebook, Inc. (http://www.facebook.com)  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef incl_HPHP_OBJECT_PROPERTY_EXPRESSION_H_
#define incl_HPHP_OBJECT_PROPERTY_EXPRESSION_H_

#include "hphp/compiler/expression/expression.h"
#include "hphp/parser/parser.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

DECLARE_BOOST_TYPES(ExpressionList);
DECLARE_BOOST_TYPES(ObjectPropertyExpression);
DECLARE_BOOST_TYPES(ClassScope);
struct Symbol;

struct ObjectPropertyExpression : Expression {
  ObjectPropertyExpression(EXPRESSION_CONSTRUCTOR_PARAMETERS,
                           ExpressionPtr object, ExpressionPtr property,
                           PropAccessType propAccessType);

  DECLARE_EXPRESSION_VIRTUAL_FUNCTIONS;

  bool isRefable(bool /*checkError*/ = false) const override { return true; }

  void setContext(Context context) override;
  void clearContext(Context context) override;

  ExpressionPtr getObject() { return m_object;}
  ExpressionPtr getProperty() { return m_property;}
  bool isNullSafe() const { return m_nullsafe; }

  bool isNonPrivate(AnalysisResultPtr ar);
  bool isValid() const { return m_valid; }
private:
  ExpressionPtr m_object;
  ExpressionPtr m_property;

  unsigned m_valid : 1;
  unsigned m_propSymValid : 1;
  unsigned m_nullsafe : 1;

  Symbol *m_propSym;
  ClassScopeRawPtr m_objectClass;
  ClassScopeRawPtr m_symOwner;

  // for avoiding code generate toObject(Variant)
  bool directVariantProxy(AnalysisResultPtr ar);
};

///////////////////////////////////////////////////////////////////////////////
}
#endif // incl_HPHP_OBJECT_PROPERTY_EXPRESSION_H_
