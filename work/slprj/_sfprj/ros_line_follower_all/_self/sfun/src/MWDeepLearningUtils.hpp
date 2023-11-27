/* Copyright 2019 The MathWorks, Inc. */

#ifndef MW_DEEP_LEARNING_UTILS_HPP
#define MW_DEEP_LEARNING_UTILS_HPP

#define LEAVE_DL_ERROR_CHECK() } }
#define CATCH_DL_ERROR_CHECK() } catch (std::runtime_error const& err) {
#define TRY_DL_ERROR_CHECK() { try {

#endif
