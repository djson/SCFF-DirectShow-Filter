﻿// Copyright 2012-2013 Alalf <alalf.iQLc_at_gmail.com>
//
// This file is part of SCFF-DirectShow-Filter(SCFF DSF).
//
// SCFF DSF is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SCFF DSF is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SCFF DSF.  If not, see <http://www.gnu.org/licenses/>.

/// @file SCFF.Common/Types.cs
/// SCFF.Commonモジュールで利用する型

/// SCFF共有クラスライブラリ
namespace SCFF.Common {

using System;

//=====================================================================
// 列挙型
//=====================================================================

/// Options用WindowState。System.Windows.WindowStateと相互に変換する。
public enum WindowState {
  Normal,     ///< 標準状態
  Minimized,  ///< 最小化
  Maximized   ///< 最大化
}

/// Profile用Windowの種類
public enum WindowTypes {
  Normal,           ///< 標準のWindow
  DesktopListView,  ///< OS別デスクトップWindow
  Desktop,          ///< ルートWindow
}
}   // namespace SCFF.Common
