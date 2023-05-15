//#define LinkedListEdit

#if defined(LinkedListEdit) && !defined(LinkedListIgnoreEdit)
#pragma message ( "LinkedList edit mode enabled!" )
#define GDEC
#define GTYPE int
#define GNAME Int
#include "LinkedList.h"
#define GDEF
#endif

#include "MemUtils.h"

#ifdef GDEF

#define LLAllocNodeFName AddLLPrefix(AllocNode)
#define LLCreateNodeFName AddLLPrefix(CreateNode)
#define LLUpdateTailFName AddLLPrefix(UpdateTail)

// Asigna memoria a un nodo.
static LLNodeName* LLAllocNodeFName(GTYPE data) {
	LLNodeName* newNode;
	CheckedMalloc(newNode, sizeof(LLNodeName));
	CheckedCopy(newNode->data, data);
	newNode->next = NULL;
	newNode->last = NULL;
	return newNode;
}

// Crea un nodo.
static LLNodeName* LLCreateNodeFName(_In_ LLName* list, GTYPE data, _Out_ bool* furtherProcessRequired) {
	LLNodeName* newNode = LLAllocNodeFName(data);
	*furtherProcessRequired = (list->head != NULL);
	if (!(*furtherProcessRequired)) {
		list->head = newNode;
		list->tail = newNode;
	}
	list->count++;
	return newNode;
}

// Estable la nueva cola de la lista.
static void LLUpdateTailFName(_In_ LLName* list, _Inout_ LLNodeName* newTail) {
	list->tail->next = newTail;
	newTail->last = list->tail;
	list->tail = newTail;
}

LLName* LLNewFName(void) {
	LLName* head;
	CheckedMalloc(head, sizeof(LLName));
	*head = (LLName){ 0, NULL, NULL };
	return head;
}

void LLDeleteFName(_In_ LLName* list) {
	LLClearFName(list);
	free(list);
}

void LLClearFName(_In_ LLName* list) {
	LLNodeName* current = list->head;
	while (current != NULL) {
		LLNodeName* next = current->next;
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
}

bool LLIterateFName(_In_ LLName* list, _Inout_ LLNodeName** currentNode) {
	if (*currentNode == NULL) return false;
	*currentNode = (*currentNode == LL_IterateStart) ? list->head : (*currentNode)->next;
	return (*currentNode != NULL);
}

_Success_(OnTrueReturn) bool LLTryFindName(_In_ LLName* list, LLSearchPredicate searchFunc, _Inout_ void* extraInfo, _Out_opt_ size_t* nodeIndex, _Out_opt_ LLNodeName** node) {
	LLNodeName* currentNode = NULL;
	size_t index = 0;
	while (LLIterateFName(list, &currentNode)) {
		if (searchFunc(&currentNode->data, index, extraInfo)) {
			if (nodeIndex != NULL) *nodeIndex = index;
			if (node != NULL) *node = currentNode;
			return true;
		}
	}
	return false;
}

void LLPrependFName(_In_ LLName* list, GTYPE data) {
	bool furtherProcessRequired;
	LLNodeName* newNode = LLCreateNodeFName(list, data, &furtherProcessRequired);
	if (!furtherProcessRequired) return;
	newNode->next = list->head;
	list->head->last = newNode;
	list->head = newNode;
}

void LLAppendFName(_In_ LLName* list, GTYPE data) {
	bool furtherProcessRequired;
	LLNodeName* newNode = LLCreateNodeFName(list, data, &furtherProcessRequired);
	if (!furtherProcessRequired) return;
	LLUpdateTailFName(list, newNode);
}

LLNodeName* LLGetNodeAtFName(_In_ LLName* list, size_t index) {
	LLNodeName* node = NULL;
	for (size_t nodeI = 0; nodeI <= index; nodeI++) {
		if (!LLIterateFName(list, &node)) {
			Throw("Index out of bounds of the list");
		}
	}
	return node;
}

void LLRemoveNodeFName(_In_ LLName* list, _In_ LLNodeName* node) {
	if (node->last != NULL) {
		node->last->next = node->next;
	} else {
		list->head = node->next;
	}
	if (node->next != NULL) {
		node->next->last = node->last;
	} else {
		list->tail = node->last;
	}
	list->count--;
	free(node);
}

void LLRemoveAtFName(_In_ LLName* list, size_t index) {
	LLNodeName* node = LLGetNodeAtFName(list, index);
	LLRemoveNodeFName(list, node);
}

void LLCwRotateFName(_In_ LLName* list) {
	if (list->count < 2) return;

	LLNodeName* newTail = list->tail->last;
	newTail->next = NULL;

	LLNodeName* newHead = list->tail;
	newHead->next = list->head;
	newHead->last = NULL;
	list->head->last = newHead;

	list->head = newHead;
	list->tail = newTail;
}

#endif
