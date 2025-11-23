/**
 * @file hash_fn.hpp
 * @brief C++ 雜湊函數的頭文件，使用命名空間和現代 C++ 數據類型。
 * @author Gemini
 * @date 2025.11.23
 */

#ifndef HASH_FN_HPP
#define HASH_FN_HPP

#include <string>
#include <iostream>

// C++ 中雜湊函數使用 HashUtils 命名空間，函數名遵循 camelCase 命名規則。
namespace HashUtils {

    /**
     * @brief 計算整數鍵的雜湊索引（除法法）。
     *
     * @param key 要雜湊的整數鍵。
     * @param m 雜湊表的大小（必須大於 0）。
     * @return 計算出的雜湊索引。
     */
    unsigned int hashIntDivision(int key, unsigned int m);

    /**
     * @brief 計算字串鍵的雜湊索引（多項式滾動雜湊法）。
     *
     * @param key 要雜湊的字串鍵 (std::string)。
     * @param m 雜湊表的大小（必須大於 0）。
     * @return 計算出的雜湊索引。
     */
    unsigned int hashStringPolynomial(const std::string& key, unsigned int m);

} // namespace HashUtils

#endif // HASH_FN_HPP