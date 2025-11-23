#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "hash_fn.hpp"

using namespace std;
using namespace HashUtils;

// 測試配置
const int NUM_INT_KEYS = 1000;
const vector<unsigned int> TABLE_SIZES = { 10, 101, 1024 };

// 測試用的固定字串鍵
const vector<string> STRING_KEYS = {
    "algorithm", "dataStructure", "compiler", "operatingSystem", "network",
    "security", "database", "programming", "hardware", "software",
    "integer", "string", "hash", "table", "index", 
    "collision", "uniform", "distribution", "analysis", "project"
};

/**
 * @brief 執行整數鍵雜湊函數的測試並輸出結果。
 * @param m 雜湊表的大小。
 */
void testIntHashing(unsigned int m) {
    cout << "--- 測試整數雜湊 (hashIntDivision) - 表大小 M=" << m << " ---\n";

    // 使用 C++ 標準庫的 map 來代替固定大小陣列，以適應任何 m
    map<unsigned int, int> indexCounts; 
    int collisions = 0;
    
    // 生成並雜湊測試鍵
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < NUM_INT_KEYS; ++i) {
        // 生成一個大範圍的整數鍵，包括負數
        int key = rand() - (RAND_MAX / 2); 
        
        unsigned int index = hashIntDivision(key, m);
        
        // 計算衝突
        if (indexCounts.count(index)) {
            collisions++;
        }
        indexCounts[index]++;
    }

    cout << "總鍵數: " << NUM_INT_KEYS << endl;
    cout << "表大小 M: " << m << endl;
    cout << "總衝突數: " << collisions << endl;
    cout << "平均桶大小: " << fixed << setprecision(2) << (double)NUM_INT_KEYS / m << endl;

    // 輸出索引分佈的簡要統計
    cout << "索引分佈（前 5 個桶）:\n";
    auto it = indexCounts.begin();
    for (int i = 0; i < 5 && it != indexCounts.end(); ++i, ++it) {
        cout << "  索引 " << it->first << ": " << it->second << " 個鍵\n";
    }

    // 檢查空桶的數量
    int emptyBuckets = 0;
    if (m > indexCounts.size()) {
        emptyBuckets = m - indexCounts.size();
    }
    cout << "空桶數量: " << emptyBuckets << " (佔總數的 " << fixed << setprecision(2) << (double)emptyBuckets / m * 100.0 << "%)\n";
    cout << "------------------------------------------------------------------\n\n";
}

/**
 * @brief 執行字串鍵雜湊函數的測試並輸出結果。
 * @param m 雜湊表的大小。
 */
void testStringHashing(unsigned int m) {
    cout << "--- 測試字串雜湊 (hashStringPolynomial) - 表大小 M=" << m << " ---\n";

    map<unsigned int, int> indexCounts;
    int collisions = 0;
    
    // 雜湊測試鍵
    for (const string& key : STRING_KEYS) {
        unsigned int index = hashStringPolynomial(key, m);
        
        cout << "鍵: \"" << key << "\" -> 索引: " << index << endl;

        // 計算衝突
        if (indexCounts.count(index)) {
            collisions++;
        }
        indexCounts[index]++;
    }

    cout << "總鍵數: " << STRING_KEYS.size() << endl;
    cout << "表大小 M: " << m << endl;
    cout << "總衝突數: " << collisions << endl;
    cout << "平均桶大小: " << fixed << setprecision(2) << (double)STRING_KEYS.size() / m << endl;

    // 檢查空桶的數量
    int emptyBuckets = 0;
    if (m > indexCounts.size()) {
        emptyBuckets = m - indexCounts.size();
    }
    cout << "空桶數量: " << emptyBuckets << " (佔總數的 " << fixed << setprecision(2) << (double)emptyBuckets / m * 100.0 << "%)\n";
    cout << "------------------------------------------------------------------\n\n";
}

/**
 * @brief 主函數。
 */
int main() {
    cout << "=== C++ 雜湊函數設計與觀察作業 ===\n\n";

    // 測試不同的表大小
    for (unsigned int m : TABLE_SIZES) {
        // 1. 測試整數雜湊
        testIntHashing(m);
        
        // 2. 測試字串雜湊
        // 僅當表大小足夠大時才測試字串，避免 m=10 時所有字串都衝突。
        if (m > STRING_KEYS.size()) {
            testStringHashing(m);
        }
    }

    return 0;
}