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

/// @file SCFF.GUI/UpdateCommands.cs
/// @copydoc SCFF::GUI::UpdateCommands

namespace SCFF.GUI {

using System.Windows.Input;

/// Profile/OptionsがUpdateされたことを他のコントロールに知らせるためのRoutedCommands
public static class UpdateCommands {
  //===================================================================
  // Profile
  //===================================================================

  /// MainWindowのUpdateByEntireProfileを呼び出す
  public static readonly RoutedCommand UpdateMainWindowByEntireProfile = new RoutedCommand();
  /// LayoutEditのUpdateByEntireProfileを呼び出す
  public static readonly RoutedCommand UpdateLayoutEditByEntireProfile = new RoutedCommand();
  /// LayoutEditのUpdateByCurrentProfileを呼び出す
  public static readonly RoutedCommand UpdateLayoutEditByCurrentProfile = new RoutedCommand();
  /// TargetWindowと更新が必要なUserControlのUpdateByCurrentProfileを呼び出す
  public static readonly RoutedCommand UpdateTargetWindowByCurrentProfile = new RoutedCommand();
  /// LayoutParameterのUpdateByCurrentProfileを呼び出す
  public static readonly RoutedCommand UpdateLayoutParameterByCurrentProfile = new RoutedCommand();

  //===================================================================
  // Options
  //===================================================================

  /// LayoutEditのUpdateByOptionsを呼び出す
  public static readonly RoutedCommand UpdateLayoutEditByOptions = new RoutedCommand();

  //===================================================================
  // RuntimeOptions
  //===================================================================
  
  /// MainWindowのUpdateByRuntimeOptionsを呼び出す
  public static readonly RoutedCommand UpdateMainWindowByRuntimeOptions = new RoutedCommand();
}
}   // namespace SCFF.GUI
