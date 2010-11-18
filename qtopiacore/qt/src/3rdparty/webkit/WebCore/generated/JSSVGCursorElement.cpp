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
#include "JSSVGCursorElement.h"

#include <wtf/GetPtr.h>

#include "JSSVGAnimatedBoolean.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedString.h"
#include "JSSVGStringList.h"
#include "SVGCursorElement.h"
#include "SVGStringList.h"

#include <runtime/Error.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGCursorElement)

/* Hash table */

static const HashTableValue JSSVGCursorElementTableValues[8] =
{
    { "x", DontDelete|ReadOnly, (intptr_t)jsSVGCursorElementX, (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)jsSVGCursorElementY, (intptr_t)0 },
    { "href", DontDelete|ReadOnly, (intptr_t)jsSVGCursorElementHref, (intptr_t)0 },
    { "requiredFeatures", DontDelete|ReadOnly, (intptr_t)jsSVGCursorElementRequiredFeatures, (intptr_t)0 },
    { "requiredExtensions", DontDelete|ReadOnly, (intptr_t)jsSVGCursorElementRequiredExtensions, (intptr_t)0 },
    { "systemLanguage", DontDelete|ReadOnly, (intptr_t)jsSVGCursorElementSystemLanguage, (intptr_t)0 },
    { "externalResourcesRequired", DontDelete|ReadOnly, (intptr_t)jsSVGCursorElementExternalResourcesRequired, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGCursorElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 31, JSSVGCursorElementTableValues, 0 };
#else
    { 17, 15, JSSVGCursorElementTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGCursorElementPrototypeTableValues[2] =
{
    { "hasExtension", DontDelete|Function, (intptr_t)jsSVGCursorElementPrototypeFunctionHasExtension, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGCursorElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGCursorElementPrototypeTableValues, 0 };
#else
    { 2, 1, JSSVGCursorElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGCursorElementPrototype::s_info = { "SVGCursorElementPrototype", 0, &JSSVGCursorElementPrototypeTable, 0 };

JSObject* JSSVGCursorElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGCursorElement>(exec, globalObject);
}

bool JSSVGCursorElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGCursorElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGCursorElement::s_info = { "SVGCursorElement", &JSSVGElement::s_info, &JSSVGCursorElementTable, 0 };

JSSVGCursorElement::JSSVGCursorElement(PassRefPtr<Structure> structure, PassRefPtr<SVGCursorElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGCursorElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGCursorElementPrototype(JSSVGCursorElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGCursorElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGCursorElement, Base>(exec, &JSSVGCursorElementTable, this, propertyName, slot);
}

JSValuePtr jsSVGCursorElementX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(static_cast<JSSVGCursorElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->xAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCursorElementY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(static_cast<JSSVGCursorElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->yAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCursorElementHref(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(static_cast<JSSVGCursorElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->hrefAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCursorElementRequiredFeatures(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(static_cast<JSSVGCursorElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->requiredFeatures()), imp);
}

JSValuePtr jsSVGCursorElementRequiredExtensions(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(static_cast<JSSVGCursorElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->requiredExtensions()), imp);
}

JSValuePtr jsSVGCursorElementSystemLanguage(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(static_cast<JSSVGCursorElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->systemLanguage()), imp);
}

JSValuePtr jsSVGCursorElementExternalResourcesRequired(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(static_cast<JSSVGCursorElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedBoolean> obj = imp->externalResourcesRequiredAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGCursorElementPrototypeFunctionHasExtension(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGCursorElement::s_info))
        return throwError(exec, TypeError);
    JSSVGCursorElement* castedThisObj = static_cast<JSSVGCursorElement*>(asObject(thisValue));
    SVGCursorElement* imp = static_cast<SVGCursorElement*>(castedThisObj->impl());
    const UString& extension = args.at(exec, 0)->toString(exec);


    JSC::JSValuePtr result = jsBoolean(imp->hasExtension(extension));
    return result;
}


}

#endif // ENABLE(SVG)
