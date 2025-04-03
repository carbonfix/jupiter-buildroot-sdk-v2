#------------------------------------------------------------
# @Copyright 2022-2023 SPACEMIT. All rights reserved.
# @Use of this source code is governed by a BSD-style license
# @that can be found in the LICENSE file.
# @
# @Author: David(qiang.fu@spacemit.com)
# @Date: 2022-12-28 11:13:50
# @LastEditTime: 2023-08-03 20:10:39
# @Description: the cmake script of al layer.
#------------------------------------------------------------

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/utils/include)

add_subdirectory(vcodec)
add_subdirectory(vps)
add_subdirectory(vi)
add_subdirectory(vo)
