﻿
// Copyright 2012 Alalf <alalf.iQLc_at_gmail.com>
//
// This file is part of SCFF DSF.
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

/// @file scff-interprocess/interprocess.h
/// @brief SCFFのプロセス間通信に関するクラス、定数、型の宣言
/// @warning To me: このファイルの中から別のファイルへのIncludeは禁止！
///- 別の言語に移植する場合もh+srcで最大2ファイルでお願いします

#ifndef SCFF_DSF_SCFF_INTERPROCESS_INTERPROCESS_H_
#define SCFF_DSF_SCFF_INTERPROCESS_INTERPROCESS_H_

#include <Windows.h>
#include <cstdint>

namespace scff_interprocess {

//=====================================================================
// SCFF Messaging Protocol v0 (by 2012/05/02 Alalf)
//
// [全体的な注意点]
// - Windows固有の型名はビットサイズが分かりにくいのでcstdintで置き換える
//   - 対応表
//     - DWORD        = uint32_t 32bit
//     - HWND(void*)  = uint64_t 64bit
//       - SCFHから変更: 念のため32bitから64bitに
//     - bool         = int8_t 8bit
// - 不動小数点数はdoubleに統一すること
//   - double: 64bit
// - すべての構造体はPOD(Plain Old Data)であること
//   - 基本型、コンストラクタ、デストラクタ、仮想関数を持たない構造体のみ
//=====================================================================

/// @brief 共有メモリ名: SCFFエントリを格納するディレクトリ
static const char kDirectoryName[] = "scff-v0-directory";

/// @brief Directoryの保護用Mutex名
static const char kDirectoryMutexName[] = "mutex-scff-v0-directory";

/// @brief 共有メモリ名の接頭辞: SCFFで使うメッセージを格納する
static const char kMessageNamePrefix[] = "scff-v0-message-";

/// @brief Messageの保護用Mutex名の接頭辞
static const char kMessageMutexNamePrefix[] = "mutex-scff-v0-message-";

/// @brief 共有メモリの接頭辞: SCFFの動作状態を格納する
static const char kInformationNamePrefix[] = "scff-v0-information-";

/// @brief Informationの保護用Mutex名の接頭辞
static const char kInformationMutexNamePrefix[] = "mutex-scff-v0-information-";

//---------------------------------------------------------------------

/// @brief Directoryに格納されるEntryの最大の数
static const int kMaxEntry = 8;

/// @brief ComplexLayout利用時の最大の要素数
static const int kMaxComplexLayoutElements = 8;

//---------------------------------------------------------------------

/// @brief レイアウトの種類
enum LayoutType {
  /// @brief 何も表示しない
  kNullLayout = 0,
  /// @brief 取り込み範囲1個で、境界は出力に強制的に合わせられる
  kNativeLayout,
  /// @brief 取り込み範囲が複数ある
  /// @warning NOT IMPLEMENTED!
  kComplexLayout
};

//---------------------------------------------------------------------

/// @brief ピクセルフォーマットの種類
/// @sa scff-imaging/imaging-types.h
/// @sa scff_imaging::ImagePixelFormat
enum ImagePixelFormat {
  /// @brief 不正なピクセルフォーマット
  kInvalidPixelFormat = -1,
  /// @brief I420(12bit)
  kI420 = 0,
  /// @brief UYVY(16bit)
  kUYVY,
  /// @brief RGB0(32bit)
  kRGB0,
  /// @brief 対応ピクセルフォーマット数
  kSupportedPixelFormatsCount
};

/// @brief 拡大縮小メソッドをあらわす定数
/// @sa scff-imaging/imaging-types.h
/// @sa scff_imaging::SWScaleFlags
enum SWScaleFlags {
  /// @brief fast bilinear
  kFastBilinear = 1,
  /// @brief bilinear
  kBilinear     = 2,
  /// @brief bicubic
  kBicubic      = 4,
  /// @brief experimental
  kX            = 8,
  /// @brief nearest neighbor
  kPoint        = 0x10,
  /// @brief averaging area
  kArea         = 0x20,
  /// @brief luma bicubic, chroma bilinear
  kBicublin     = 0x40,
  /// @brief gaussian
  kGauss        = 0x80,
  /// @brief sinc
  kSinc         = 0x100,
  /// @brief natural
  kLanczos      = 0x200,
  /// @brief natural bicubic spline
  kSpline       = 0x400
};

/// @brief エラーコードを表す定数
/// @sa scff-imaging/imaging-types.h
/// @sa scff_imaging::ErrorCode
enum ErrorCode {
  /// @brief エラーはない
  kNoError = 0,
  /// @brief 初期化されていない
  kUninitialziedError,
  /// @brief 対応してないType
  kImageTypeError,
  /// @brief メモリの確保に失敗した
  kOutOfMemoryError,
  /// @brief 一回しか初期化・生成は許されていない
  kMultipleCreateError,
  /// @brief 対応してないPixelFormat
  kPixelFormatError,
  /// @brief 不正なウィンドウハンドル
  kInvalidWindowError,
  /// @brief クリッピング領域が不正
  kInvalidClippingRegionError,
  /// @brief キャプチャ領域が動作中に不正になった
  kInvalidCaptureRegionError,
  /// @brief 取り込み時に画面の色深度が32bitではなかった
  kNot32bitColorError
};

//---------------------------------------------------------------------

// アラインメントをコンパイラに変えられないように
#pragma pack(push, 1)
/// @brief 共有メモリ(Directory)に格納する構造体のエントリ
struct Entry {
  /// @brief SCFF DSFのDLLが使われれているプロセスID
  uint32_t process_id;
  /// @brief SCFF DSFのDLLが使われているプロセス名
  /// @warning 長さが制限されているので注意！
  char process_name[MAX_PATH];
  /// @brief サンプルの出力width
  int32_t sample_width;
  /// @brief サンプルの出力height
  int32_t sample_height;
  /// @brief サンプルの出力ピクセルフォーマット
  /// @attention ImagePixelFormatを操作に使うこと
  int32_t sample_image_pixel_format;
  /// @brief 目標fps
  double fps;
};

/// @brief 共有メモリ(Directory)に格納する構造体
struct Directory {
  Entry entries[kMaxEntry];
};

/// @brief レイアウトパラメータ
/// @sa scff_imaging::ScreenCaptureParameter
struct LayoutParameter {
  /// @brief サンプル内の原点のX座標
  /// @warning NullLayout,NativeLayoutでは無視される
  int32_t bound_x;
  /// @brief サンプル内の原点のY座標
  /// @warning NullLayout,NativeLayoutでは無視される
  int32_t bound_y;
  /// @brief サンプル内の幅
  /// @warning NullLayout,NativeLayoutでは無視される
  int32_t bound_width;
  /// @brief サンプル内の高さ
  /// @warning NullLayout,NativeLayoutでは無視される
  int32_t bound_height;
  /// @brief キャプチャを行う対象となるウィンドウ
  uint64_t window;
  /// @brief 取り込み範囲の開始X座標
  int32_t clipping_x;
  /// @brief 取り込み範囲の開始y座標
  int32_t clipping_y;
  /// @brief 取り込み範囲の幅
  int32_t clipping_width;
  /// @brief 取り込み範囲の高さ
  int32_t clipping_height;
  /// @brief マウスカーソルの表示
  int8_t show_cursor;
  /// @brief レイヤードウィンドウの表示
  int8_t show_layered_window;
  /// @brief 拡大縮小アルゴリズムの選択
  /// @attention SWScaleFlagsを操作に使うこと
  int32_t sws_flags;
  /// @brief 取り込み範囲が出力サイズより小さい場合拡張
  int8_t stretch;
  /// @brief アスペクト比の保持
  int8_t keep_aspect_ratio;
};

/// @brief 共有メモリ(Message)に格納する構造体
struct Message {
  /// @brief タイムスタンプ(time()で求められたものを想定)
  /// @warning 1ではじまり単調増加が必須条件
  /// @warning (0および負数は無効なメッセージを示す)
  int64_t timestamp;
  /// @brief レイアウトの種類
  /// @attention LayoutTypeを操作に使うこと
  int32_t layout_type;
  /// @brief 有効なレイアウト要素の数
  int32_t layout_element_count;
  /// @brief レイアウトパラメータの配列
  LayoutParameter
      layout_parameters[kMaxComplexLayoutElements];
};

/// @brief 共有メモリ(Information)に格納する構造体
struct Information {
  /// @brief engineのエラーコード
  /// @attention ErrorCodeを操作に使うこと
  int32_t engine_error_code;
  /// @brief engine.layout_のエラーコード
  /// @attention ErrorCodeを操作に使うこと
  int32_t layout_error_code;
  /// @brief 1秒間あたりの処理時間(Sec)
  double process_time;
};
#pragma pack(pop)

//---------------------------------------------------------------------

/// @brief SCFFのプロセス間通信を担当するクラス
class Interprocess {
 public:
  /// @brief コンストラクタ
  Interprocess();
  /// @brief デストラクタ
  ~Interprocess();

  /// @brief Directory初期化
  bool InitDirectory();
  /// @brief Directoryの初期化が成功したか
  bool IsDirectoryInitialized();

  /// @brief Setter: プロセスID
  void set_process_id(uint32_t process_id);

  /// @brief Message初期化
  /// @pre set_process_id実行済み
  bool InitMessage();
  /// @brief Messageの初期化が成功したか
  bool IsMessageInitialized();

  /// @brief Information初期化
  /// @pre set_process_id実行済み
  bool InitInformation();
  /// @brief Informationの初期化が成功したか
  bool IsInformationInitialized();

  //-------------------------------------------------------------------
  // for SCFF DirectShow Filter
  //-------------------------------------------------------------------
  /// @brief エントリを作成する
  bool AddEntry(const Entry &entry);
  /// @brief エントリを削除する
  bool RemoveEntry();
  /// @brief メッセージを受け取る
  bool ReceiveMessage(Message *message);
  /// @brief モニタリング情報を更新する
  bool UpdateInformation(const Information &information);
  //-------------------------------------------------------------------

  /// @brief ディレクトリを取得する
  bool GetDirectory(Directory *directory);
  /// @brief メッセージを作成する
  bool SendMessage(const Message &message);
  /// @brief モニタリング情報を取得する
  bool CheckInformation(const Information &information);

 private:
  /// @brief Directory解放
  void ReleaseDirectory();
  /// @brief Message解放
  void ReleaseMessage();
  /// @brief Information解放
  void ReleaseInformation();

  /// @brief 共有メモリ: Directory
  HANDLE directory_;
  /// @brief ビュー: Directory
  LPVOID view_of_directory_;
  /// @brief Mutex: Directory
  HANDLE mutex_directory_;

  /// @brief プロセスID
  uint32_t process_id_;

  /// @brief 共有メモリ: Message
  HANDLE message_;
  /// @brief ビュー: Message
  LPVOID view_of_message_;
  /// @brief Mutex: Message
  HANDLE mutex_message_;

  /// @brief 共有メモリ: Information
  HANDLE information_;
  /// @brief ビュー: Information
  LPVOID view_of_information_;
  /// @brief Mutex: Information
  HANDLE mutex_information_;
};
}   // namespace scff_interprocess

#endif  // SCFF_DSF_SCFF_INTERPROCESS_INTERPROCESS_H_