#pragma once

#define ComponentOfType(type) typeid(type)

typedef const type_info& ComponentType;

#define GetComponentOfType(gameObject, type) dynamic_cast<type*>(gameObject.GetComponent(ComponentOfType(type)))