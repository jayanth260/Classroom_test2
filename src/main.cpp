#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <immintrin.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <cstdint>
#include <filesystem>
#include <string>

namespace solution {
std::string compute(const std::string& m1_path, const std::string& m2_path, int n, int k, int m) {
    std::string sol_path = std::filesystem::temp_directory_path() / "student_sol.dat";
    std::ofstream sol_fs(sol_path, std::ios::binary);
    std::ifstream m1_fs(m1_path, std::ios::binary), m2_fs(m2_path, std::ios::binary);

    const auto m1 = std::make_unique<float[]>(n * k);
    const auto m2 = std::make_unique<float[]>(k * m);
    auto result = std::make_unique<float[]>(n * m);

    m1_fs.read(reinterpret_cast<char*>(m1.get()), sizeof(float) * n * k);
    m2_fs.read(reinterpret_cast<char*>(m2.get()), sizeof(float) * k * m);

    m1_fs.close();
    m2_fs.close();

       for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[j*m+k] += m1[j * n + i] * m2[i * n + k];
            }
        }
    }


    sol_fs.write(reinterpret_cast<const char*>(result.get()), sizeof(float) * n * m);
    sol_fs.close();

    return sol_path;
}
}