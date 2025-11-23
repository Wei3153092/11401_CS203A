/**
 * @file hash_fn.h
 * @brief 雜湊函數的頭文件，包含函數原型和常量定義。
 * @author Gemini
 * @date 2025.11.23
 */

#ifndef HASH_FN_H
#define HASH_FN_H

#include <stddef.h> // for size_t

// C 語言中雜湊函數的函數頭文件遵循 snake_case 命名規則。

/**
 * @brief 計算整數鍵的雜湊索引（除法法）。
 *
 * 這是最簡單的雜湊方法，索引 = key mod m。
 *
 * @param key 要雜湊的整數鍵。
 * @param m 雜湊表的大小（必須大於 0）。
 * @return 計算出的雜湊索引。
 */
unsigned int hash_int_division(int key, unsigned int m);

/**
 * @brief 計算字串鍵的雜湊索引（多項式滾動雜湊法）。
 *
 * 使用 a=31 作為乘數，透過累加字串中每個字元的加權值來減少衝突。
 * 這是業界常用的雜湊函數設計。
 *
 * @param key 要雜湊的字串鍵（以 null 結尾）。
 * @param m 雜湊表的大小（必須大於 0）。
 * @return 計算出的雜湊索引。
 */
unsigned int hash_string_polynomial(const char* key, unsigned int m);

#endif // HASH_FN_H