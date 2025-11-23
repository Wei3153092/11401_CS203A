#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash_fn.h"

// 測試配置
#define NUM_INT_KEYS 1000  // 測試的整數鍵數量
#define NUM_TABLE_SIZES 3  // 測試的表大小數量
#define MAX_INDEX_COUNT 1024 // 最大的表大小（用於結果數組）

// 測試用的固定字串鍵
const char* string_keys[] = {
    "apple", "banana", "cherry", "date", "elderberry", 
    "fig", "grape", "honeydew", "kiwi", "lemon",
    "lime", "mango", "nectarine", "orange", "papaya",
    "peach", "quince", "raspberry", "strawberry", "tangerine"
};
#define NUM_STRING_KEYS (sizeof(string_keys) / sizeof(string_keys[0]))

// 測試的雜湊表大小 m
const unsigned int table_sizes[NUM_TABLE_SIZES] = { 10, 101, 1024 };

/**
 * @brief 執行整數鍵雜湊函數的測試並輸出結果。
 * @param m 雜湊表的大小。
 */
void test_int_hashing(unsigned int m) {
    printf("--- 測試整數雜湊 (hash_int_division) - 表大小 M=%u ---\n", m);

    // 記錄每個索引的鍵數量（桶）
    int index_counts[MAX_INDEX_COUNT] = {0}; 
    int collisions = 0;
    
    // 生成並雜湊測試鍵
    srand(time(NULL));
    for (int i = 0; i < NUM_INT_KEYS; ++i) {
        // 生成一個大範圍的整數鍵，包括負數
        int key = rand() - (RAND_MAX / 2); 
        
        unsigned int index = hash_int_division(key, m);
        
        // 確保索引在範圍內
        if (index >= m || index >= MAX_INDEX_COUNT) {
            fprintf(stderr, "錯誤：計算出的索引超出範圍！\n");
            continue;
        }

        // 記錄索引計數並計算衝突
        if (index_counts[index] > 0) {
            collisions++;
        }
        index_counts[index]++;
    }

    printf("總鍵數: %d\n", NUM_INT_KEYS);
    printf("表大小 M: %u\n", m);
    printf("總衝突數: %d\n", collisions);
    printf("平均桶大小: %.2f\n", (float)NUM_INT_KEYS / m);

    // 輸出前 5 個桶的統計數據
    printf("索引分佈（前 5 個桶）:\n");
    for (unsigned int i = 0; i < m && i < 5; ++i) {
        printf("  索引 %u: %d 個鍵\n", i, index_counts[i]);
    }

    // 檢查空桶的數量
    int empty_buckets = 0;
    for (unsigned int i = 0; i < m; ++i) {
        if (index_counts[i] == 0) {
            empty_buckets++;
        }
    }
    printf("空桶數量: %d (佔總數的 %.2f%%)\n", empty_buckets, (float)empty_buckets / m * 100.0);
    printf("------------------------------------------------------------------\n\n");
}

/**
 * @brief 執行字串鍵雜湊函數的測試並輸出結果。
 * @param m 雜湊表的大小。
 */
void test_string_hashing(unsigned int m) {
    printf("--- 測試字串雜湊 (hash_string_polynomial) - 表大小 M=%u ---\n", m);

    // 由於鍵數少，我們使用一個簡單的陣列來記錄索引計數
    int index_counts[MAX_INDEX_COUNT] = {0};
    int collisions = 0;
    
    // 雜湊測試鍵
    for (size_t i = 0; i < NUM_STRING_KEYS; ++i) {
        const char* key = string_keys[i];
        unsigned int index = hash_string_polynomial(key, m);
        
        if (index >= m || index >= MAX_INDEX_COUNT) {
            fprintf(stderr, "錯誤：計算出的索引超出範圍！\n");
            continue;
        }

        printf("鍵: \"%s\" -> 索引: %u\n", key, index);

        // 記錄索引計數並計算衝突
        if (index_counts[index] > 0) {
            collisions++;
        }
        index_counts[index]++;
    }

    printf("總鍵數: %d\n", NUM_STRING_KEYS);
    printf("表大小 M: %u\n", m);
    printf("總衝突數: %d\n", collisions);
    printf("平均桶大小: %.2f\n", (float)NUM_STRING_KEYS / m);

    // 檢查空桶的數量
    int empty_buckets = 0;
    for (unsigned int i = 0; i < m; ++i) {
        if (index_counts[i] == 0) {
            empty_buckets++;
        }
    }
    printf("空桶數量: %d (佔總數的 %.2f%%)\n", empty_buckets, (float)empty_buckets / m * 100.0);
    printf("------------------------------------------------------------------\n\n");
}

/**
 * @brief 主函數。
 */
int main(void) {
    printf("=== C 雜湊函數設計與觀察作業 ===\n\n");

    // 測試不同的表大小
    for (int i = 0; i < NUM_TABLE_SIZES; ++i) {
        unsigned int m = table_sizes[i];
        
        // 1. 測試整數雜湊
        test_int_hashing(m);
        
        // 2. 測試字串雜湊
        // 僅當表大小足夠大時才測試字串，避免 m=10 時所有字串都衝突。
        if (m > NUM_STRING_KEYS) {
            test_string_hashing(m);
        }
    }

    return 0;
}