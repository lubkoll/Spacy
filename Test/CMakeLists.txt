find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

aux_source_directory(Mock MOCK_SRC_LIST)
add_library(mocks ${MOCK_SRC_LIST})
target_link_libraries(mocks PUBLIC Spacy::Spacy)


aux_source_directory(Spacy TEST_SRC_LIST)
if(Eigen3_FOUND)
  aux_source_directory(Spacy/Adaptivity TEST_SRC_LIST)
  list(APPEND TEST_SRC_LIST
      Spacy/Algorithm/ODEInt.cpp
  )
endif()
aux_source_directory(Spacy/Algorithm/CompositeStep TEST_SRC_LIST)
aux_source_directory(Spacy/Algorithm/Scalar TEST_SRC_LIST)
aux_source_directory(Spacy/Algorithm/Generic TEST_SRC_LIST)
aux_source_directory(Spacy/Algorithm/Newton/Scalar TEST_SRC_LIST)
aux_source_directory(Spacy/Spaces TEST_SRC_LIST)
aux_source_directory(Spacy/Spaces/ScalarSpace TEST_SRC_LIST)
aux_source_directory(Spacy/Spaces/ProductSpace TEST_SRC_LIST)
aux_source_directory(Spacy/Spaces/PrimalDualProductSpace TEST_SRC_LIST)
aux_source_directory(Spacy/Util TEST_SRC_LIST)
aux_source_directory(Spacy/Util/Base TEST_SRC_LIST)
aux_source_directory(Spacy/Util/Mixins TEST_SRC_LIST)

list(APPEND TEST_SRC_LIST
    Spacy/Algorithm/dampingFactor.cpp
    Spacy/Algorithm/lipschitzConstant.cpp
)

include(CTest)
enable_testing()
foreach(TEST ${TEST_SRC_LIST})
  get_filename_component(TEST_NAME ${TEST} NAME_WE)
  get_filename_component(TEST_DIR ${TEST} DIRECTORY)
  string(REGEX REPLACE "/" "_" TEST_DIR ${TEST_DIR})
  set(TEST_UNIQUE_NAME "${TEST_DIR}_${TEST_NAME}")
  add_executable(${TEST_UNIQUE_NAME} ${TEST})
  target_link_libraries(${TEST_UNIQUE_NAME} mocks Spacy::Spacy GTest::GTest ${GMOCK_LIBRARIES} Threads::Threads)
  add_test(${TEST_UNIQUE_NAME} ${PROJECT_BINARY_DIR}/Test/${TEST_UNIQUE_NAME})
endforeach()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
