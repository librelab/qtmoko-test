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

#include "JSMutationEvent.h"

#include <wtf/GetPtr.h>

#include "JSNode.h"
#include "KURL.h"
#include "MutationEvent.h"
#include "Node.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSMutationEvent)

/* Hash table */

static const HashTableValue JSMutationEventTableValues[7] =
{
    { "relatedNode", DontDelete|ReadOnly, (intptr_t)jsMutationEventRelatedNode, (intptr_t)0 },
    { "prevValue", DontDelete|ReadOnly, (intptr_t)jsMutationEventPrevValue, (intptr_t)0 },
    { "newValue", DontDelete|ReadOnly, (intptr_t)jsMutationEventNewValue, (intptr_t)0 },
    { "attrName", DontDelete|ReadOnly, (intptr_t)jsMutationEventAttrName, (intptr_t)0 },
    { "attrChange", DontDelete|ReadOnly, (intptr_t)jsMutationEventAttrChange, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsMutationEventConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSMutationEventTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSMutationEventTableValues, 0 };
#else
    { 17, 15, JSMutationEventTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSMutationEventConstructorTableValues[4] =
{
    { "MODIFICATION", DontDelete|ReadOnly, (intptr_t)jsMutationEventMODIFICATION, (intptr_t)0 },
    { "ADDITION", DontDelete|ReadOnly, (intptr_t)jsMutationEventADDITION, (intptr_t)0 },
    { "REMOVAL", DontDelete|ReadOnly, (intptr_t)jsMutationEventREMOVAL, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSMutationEventConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSMutationEventConstructorTableValues, 0 };
#else
    { 8, 7, JSMutationEventConstructorTableValues, 0 };
#endif

class JSMutationEventConstructor : public DOMObject {
public:
    JSMutationEventConstructor(ExecState* exec)
        : DOMObject(JSMutationEventConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSMutationEventPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValuePtr proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSMutationEventConstructor::s_info = { "MutationEventConstructor", 0, &JSMutationEventConstructorTable, 0 };

bool JSMutationEventConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSMutationEventConstructor, DOMObject>(exec, &JSMutationEventConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSMutationEventPrototypeTableValues[5] =
{
    { "MODIFICATION", DontDelete|ReadOnly, (intptr_t)jsMutationEventMODIFICATION, (intptr_t)0 },
    { "ADDITION", DontDelete|ReadOnly, (intptr_t)jsMutationEventADDITION, (intptr_t)0 },
    { "REMOVAL", DontDelete|ReadOnly, (intptr_t)jsMutationEventREMOVAL, (intptr_t)0 },
    { "initMutationEvent", DontDelete|Function, (intptr_t)jsMutationEventPrototypeFunctionInitMutationEvent, (intptr_t)8 },
    { 0, 0, 0, 0 }
};

static const HashTable JSMutationEventPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSMutationEventPrototypeTableValues, 0 };
#else
    { 8, 7, JSMutationEventPrototypeTableValues, 0 };
#endif

const ClassInfo JSMutationEventPrototype::s_info = { "MutationEventPrototype", 0, &JSMutationEventPrototypeTable, 0 };

JSObject* JSMutationEventPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSMutationEvent>(exec, globalObject);
}

bool JSMutationEventPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSMutationEventPrototype, JSObject>(exec, &JSMutationEventPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSMutationEvent::s_info = { "MutationEvent", &JSEvent::s_info, &JSMutationEventTable, 0 };

JSMutationEvent::JSMutationEvent(PassRefPtr<Structure> structure, PassRefPtr<MutationEvent> impl)
    : JSEvent(structure, impl)
{
}

JSObject* JSMutationEvent::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSMutationEventPrototype(JSMutationEventPrototype::createStructure(JSEventPrototype::self(exec, globalObject)));
}

bool JSMutationEvent::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSMutationEvent, Base>(exec, &JSMutationEventTable, this, propertyName, slot);
}

JSValuePtr jsMutationEventRelatedNode(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    MutationEvent* imp = static_cast<MutationEvent*>(static_cast<JSMutationEvent*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->relatedNode()));
}

JSValuePtr jsMutationEventPrevValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    MutationEvent* imp = static_cast<MutationEvent*>(static_cast<JSMutationEvent*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->prevValue());
}

JSValuePtr jsMutationEventNewValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    MutationEvent* imp = static_cast<MutationEvent*>(static_cast<JSMutationEvent*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->newValue());
}

JSValuePtr jsMutationEventAttrName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    MutationEvent* imp = static_cast<MutationEvent*>(static_cast<JSMutationEvent*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->attrName());
}

JSValuePtr jsMutationEventAttrChange(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    MutationEvent* imp = static_cast<MutationEvent*>(static_cast<JSMutationEvent*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->attrChange());
}

JSValuePtr jsMutationEventConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSMutationEvent*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValuePtr JSMutationEvent::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSMutationEventConstructor>(exec);
}

JSValuePtr jsMutationEventPrototypeFunctionInitMutationEvent(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSMutationEvent::s_info))
        return throwError(exec, TypeError);
    JSMutationEvent* castedThisObj = static_cast<JSMutationEvent*>(asObject(thisValue));
    MutationEvent* imp = static_cast<MutationEvent*>(castedThisObj->impl());
    const UString& type = args.at(exec, 0)->toString(exec);
    bool canBubble = args.at(exec, 1)->toBoolean(exec);
    bool cancelable = args.at(exec, 2)->toBoolean(exec);
    Node* relatedNode = toNode(args.at(exec, 3));
    const UString& prevValue = args.at(exec, 4)->toString(exec);
    const UString& newValue = args.at(exec, 5)->toString(exec);
    const UString& attrName = args.at(exec, 6)->toString(exec);
    unsigned short attrChange = args.at(exec, 7)->toInt32(exec);

    imp->initMutationEvent(type, canBubble, cancelable, relatedNode, prevValue, newValue, attrName, attrChange);
    return jsUndefined();
}

// Constant getters

JSValuePtr jsMutationEventMODIFICATION(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValuePtr jsMutationEventADDITION(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValuePtr jsMutationEventREMOVAL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}


}