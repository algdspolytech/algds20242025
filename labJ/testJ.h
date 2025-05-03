#pragma once

void TestInsert_EmptyTable_ReturnSuccess();

void TestInsert_DuplicateKey_ReturnFailure();

void TestSearch_NonExistentKey_ReturnFailure();

void TestDelete_ExistingKey_ReturnSuccess();

void TestDelete_NonExistentKey_ReturnFailure();

void TestCollisionHandling_TwoKeysSameHash_ReturnBothExist();

void TestFullTable_InsertBeyondCapacity_ReturnFailure();

void TestReuseDeletedSlot_InsertAfterDelete_ReturnSuccess();

void TestFreeTable_ClearMemory_AllSlotsEmpty();

void TestComplexScenario_MultipleOperations_ReturnConsistent();

void test();