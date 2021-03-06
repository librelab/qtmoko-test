/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"


#if ENABLE(SVG)

#include "SVGElement.h"
#include "JSSVGCircleElement.h"

#include <wtf/GetPtr.h>

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedBoolean.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedString.h"
#include "JSSVGAnimatedTransformList.h"
#include "JSSVGElement.h"
#include "JSSVGMatrix.h"
#include "JSSVGRect.h"
#include "JSSVGStringList.h"
#include "KURL.h"
#include "SVGCircleElement.h"
#include "SVGElement.h"
#include "SVGStringList.h"

#include <runtime/Error.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGCircleElement)

/* Hash table */

static const HashTableValue JSSVGCircleElementTableValues[15] =
{
    { "cx", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementCx, (intptr_t)0 },
    { "cy", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementCy, (intptr_t)0 },
    { "r", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementR, (intptr_t)0 },
    { "requiredFeatures", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementRequiredFeatures, (intptr_t)0 },
    { "requiredExtensions", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementRequiredExtensions, (intptr_t)0 },
    { "systemLanguage", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementSystemLanguage, (intptr_t)0 },
    { "xmllang", DontDelete, (intptr_t)jsSVGCircleElementXmllang, (intptr_t)setJSSVGCircleElementXmllang },
    { "xmlspace", DontDelete, (intptr_t)jsSVGCircleElementXmlspace, (intptr_t)setJSSVGCircleElementXmlspace },
    { "externalResourcesRequired", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementExternalResourcesRequired, (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementClassName, (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementStyle, (intptr_t)0 },
    { "transform", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementTransform, (intptr_t)0 },
    { "nearestViewportElement", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementNearestViewportElement, (intptr_t)0 },
    { "farthestViewportElement", DontDelete|ReadOnly, (intptr_t)jsSVGCircleElementFarthestViewportElement, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGCircleElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSSVGCircleElementTableValues, 0 };
#else
    { 34, 31, JSSVGCircleElementTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGCircleElementPrototypeTableValues[7] =
{
    { "hasExtension", DontDelete|Function, (intptr_t)jsSVGCircleElementPrototypeFunctionHasExtension, (intptr_t)1 },
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)jsSVGCircleElementPrototypeFunctionGetPresentationAttribute, (intptr_t)1 },
    { "getBBox", DontDelete|Function, (intptr_t)jsSVGCircleElementPrototypeFunctionGetBBox, (intptr_t)0 },
    { "getCTM", DontDelete|Function, (intptr_t)jsSVGCircleElementPrototypeFunctionGetCTM, (intptr_t)0 },
    { "getScreenCTM", DontDelete|Function, (intptr_t)jsSVGCircleElementPrototypeFunctionGetScreenCTM, (intptr_t)0 },
    { "getTransformToElement", DontDelete|Function, (intptr_t)jsSVGCircleElementPrototypeFunctionGetTransformToElement, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGCircleElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 2047, JSSVGCircleElementPrototypeTableValues, 0 };
#else
    { 17, 15, JSSVGCircleElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGCircleElementPrototype::s_info = { "SVGCircleElementPrototype", 0, &JSSVGCircleElementPrototypeTable, 0 };

JSObject* JSSVGCircleElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGCircleElement>(exec, globalObject);
}

bool JSSVGCircleElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGCircleElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGCircleElement::s_info = { "SVGCircleElement", &JSSVGElement::s_info, &JSSVGCircleElementTable, 0 };

JSSVGCircleElement::JSSVGCircleElement(PassRefPtr<Structure> structure, PassRefPtr<SVGCircleElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGCircleElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGCircleElementPrototype(JSSVGCircleElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGCircleElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGCircleElement, Base>(exec, &JSSVGCircleElementTable, this, propertyName, slot);
}

JSValuePtr jsSVGCircleElementCx(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->cxAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCircleElementCy(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->cyAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCircleElementR(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->rAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCircleElementRequiredFeatures(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->requiredFeatures()), imp);
}

JSValuePtr jsSVGCircleElementRequiredExtensions(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->requiredExtensions()), imp);
}

JSValuePtr jsSVGCircleElementSystemLanguage(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->systemLanguage()), imp);
}

JSValuePtr jsSVGCircleElementXmllang(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->xmllang());
}

JSValuePtr jsSVGCircleElementXmlspace(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->xmlspace());
}

JSValuePtr jsSVGCircleElementExternalResourcesRequired(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedBoolean> obj = imp->externalResourcesRequiredAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCircleElementClassName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCircleElementStyle(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->style()));
}

JSValuePtr jsSVGCircleElementTransform(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedTransformList> obj = imp->transformAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCircleElementNearestViewportElement(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->nearestViewportElement()));
}

JSValuePtr jsSVGCircleElementFarthestViewportElement(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->farthestViewportElement()));
}

void JSSVGCircleElement::put(ExecState* exec, const Identifier& propertyName, JSValuePtr value, PutPropertySlot& slot)
{
    lookupPut<JSSVGCircleElement, Base>(exec, propertyName, value, &JSSVGCircleElementTable, this, slot);
}

void setJSSVGCircleElementXmllang(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(thisObject)->impl());
    imp->setXmllang(value->toString(exec));
}

void setJSSVGCircleElementXmlspace(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(static_cast<JSSVGCircleElement*>(thisObject)->impl());
    imp->setXmlspace(value->toString(exec));
}

JSValuePtr jsSVGCircleElementPrototypeFunctionHasExtension(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGCircleElement::s_info))
        return throwError(exec, TypeError);
    JSSVGCircleElement* castedThisObj = static_cast<JSSVGCircleElement*>(asObject(thisValue));
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(castedThisObj->impl());
    const UString& extension = args.at(exec, 0)->toString(exec);


    JSC::JSValuePtr result = jsBoolean(imp->hasExtension(extension));
    return result;
}

JSValuePtr jsSVGCircleElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGCircleElement::s_info))
        return throwError(exec, TypeError);
    JSSVGCircleElement* castedThisObj = static_cast<JSSVGCircleElement*>(asObject(thisValue));
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(castedThisObj->impl());
    const UString& name = args.at(exec, 0)->toString(exec);


    JSC::JSValuePtr result = toJS(exec, WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}

JSValuePtr jsSVGCircleElementPrototypeFunctionGetBBox(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGCircleElement::s_info))
        return throwError(exec, TypeError);
    JSSVGCircleElement* castedThisObj = static_cast<JSSVGCircleElement*>(asObject(thisValue));
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(castedThisObj->impl());


    JSC::JSValuePtr result = toJS(exec, JSSVGStaticPODTypeWrapper<FloatRect>::create(imp->getBBox()).get(), imp);
    return result;
}

JSValuePtr jsSVGCircleElementPrototypeFunctionGetCTM(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGCircleElement::s_info))
        return throwError(exec, TypeError);
    JSSVGCircleElement* castedThisObj = static_cast<JSSVGCircleElement*>(asObject(thisValue));
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(castedThisObj->impl());


    JSC::JSValuePtr result = toJS(exec, JSSVGStaticPODTypeWrapper<TransformationMatrix>::create(imp->getCTM()).get(), imp);
    return result;
}

JSValuePtr jsSVGCircleElementPrototypeFunctionGetScreenCTM(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGCircleElement::s_info))
        return throwError(exec, TypeError);
    JSSVGCircleElement* castedThisObj = static_cast<JSSVGCircleElement*>(asObject(thisValue));
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(castedThisObj->impl());


    JSC::JSValuePtr result = toJS(exec, JSSVGStaticPODTypeWrapper<TransformationMatrix>::create(imp->getScreenCTM()).get(), imp);
    return result;
}

JSValuePtr jsSVGCircleElementPrototypeFunctionGetTransformToElement(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGCircleElement::s_info))
        return throwError(exec, TypeError);
    JSSVGCircleElement* castedThisObj = static_cast<JSSVGCircleElement*>(asObject(thisValue));
    SVGCircleElement* imp = static_cast<SVGCircleElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    SVGElement* element = toSVGElement(args.at(exec, 0));


    JSC::JSValuePtr result = toJS(exec, JSSVGStaticPODTypeWrapper<TransformationMatrix>::create(imp->getTransformToElement(element, ec)).get(), imp);
    setDOMException(exec, ec);
    return result;
}


}

#endif // ENABLE(SVG)
