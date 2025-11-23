/**
 * @file hash_fn.c
 * @brief 雜湊函數的實作，用於整數鍵和字串鍵。
 * @author Gemini
 * @date 2025.11.23
 */

#include "hash_fn.h"
#include <limits.h>

// 實現整數鍵雜湊函數
unsigned int hash_int_division(int key, unsigned int m) {
    // 錯誤處理：表大小 m 必須大於 0
    if (m == 0) {
        // 在實際應用中，會記錄錯誤或終止程式。這裡返回 0 以避免除以零。
        return 0; 
    }

    // 處理負數鍵：將其轉換為正數。
    // 使用 long long 以避免 INT_MIN 的絕對值溢出 int。
    long long positive_key = (long long)key;
    if (positive_key < 0) {
        positive_key = -positive_key;
    }

    // 除法法：h(key) = key mod m
    return (unsigned int)(positive_key % m);
}

// 實現字串鍵雜湊函數（多項式滾動雜湊）
unsigned int hash_string_polynomial(const char* key, unsigned int m) {
    // 錯誤處理：表大小 m 必須大於 0
    if (m == 0) {
        return 0;
    }

    // 檢查空指針
    if (key == NULL) {
        return 0; 
    }

    unsigned int hash_value = 0;
    const unsigned int P_MULTIPLIER = 31; // 常用的素數乘數

    // 迭代字串中的每個字元
    for (size_t i = 0; key[i] != '\0'; ++i) {
        // 多項式滾動雜湊的核心計算: hash = hash * P_MULTIPLIER + key[i]
        // 由於我們使用 unsigned int，溢出會自動進行模 2^32 運算。
        // 這與在每個步驟都進行 % m 類似，但更高效。
        hash_value = (hash_value * P_MULTIPLIER) + (unsigned int)key[i];
    }

    // 最後一步：將最終值模 m，得到雜湊表索引。
    return hash_value % m;
}