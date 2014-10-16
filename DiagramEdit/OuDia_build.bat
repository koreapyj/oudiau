rem OuDia ビルド


rem  --------------------------------
rem ビルド環境設定
rem  --------------------------------

rem TODO: vcvars32.bat のパスを、お使いの環境に合わせて変更してください。
call "%VS90COMNTOOLS%vsvars32"

rem TODO: HTML Help Workshop に含まれる hhc.exe のパスを、
rem お使いの環境に合わせて変更してください。
rem SET HHC="C:\Program Files\HTML Help Workshop\hhc"
SET HHC="D:\Program Files (x86)\HTML Help Workshop\hhc"

rem TODO: コンバータDLLのビルドを行わない場合は、下の行の rem を削除してください。
rem set CONVFILEDLL_NOT_BUILD=1


rem  --------------------------------
rem (1)　コンバータDLL
rem  --------------------------------

if "%CONVFILEDLL_NOT_BUILD%"=="1" goto CONVFILE_END

pushd ConvDedFile\ConvFileOudia02To03
rem カレントディレクトリ=このバッチファイルのディレクトリ\ConvDedFile\ConvFileOudia02To03

call devenv ConvFileOudia02To03.sln /build "Release" 

popd
rem カレントディレクトリ=このバッチファイルのディレクトリ


pushd ConvDedFile\ConvFileOudia03To05
rem カレントディレクトリ=このバッチファイルのディレクトリ\ConvDedFile\ConvFileOudia03To05

call devenv ConvFileOudia03To05.sln /build "Release" 

popd
rem カレントディレクトリ=このバッチファイルのディレクトリ

pushd ConvDedFile\ConvFileOudia05To06
rem カレントディレクトリ=このバッチファイルのディレクトリ\ConvDedFile\ConvFileOudia05To06

call devenv ConvFileOudia05To06.sln /build "Release" 

popd
rem カレントディレクトリ=このバッチファイルのディレクトリ

pushd ConvDedFile\ConvFileOudia06To101
rem カレントディレクトリ=このバッチファイルのディレクトリ\ConvDedFile\ConvFileOudia06To101

call devenv ConvFileOudia06To101.sln /build "Release" 

popd
rem カレントディレクトリ=このバッチファイルのディレクトリ



pushd ConvDedFile\ConvFileOudia101To102
rem カレントディレクトリ=このバッチファイルのディレクトリ\ConvDedFile\ConvFileOudia101To102

call devenv ConvFileOudia101To102.sln /build "Release" 

popd
rem カレントディレクトリ=このバッチファイルのディレクトリ



:CONVFILE_END

rem  --------------------------------
rem (2)　マニュアルの .chm
rem  --------------------------------

pushd manual

call %HHC% oudia.hhp
copy oudia.chm ..\Release


popd 


rem  --------------------------------
rem (3)リリース版ソフト
rem  --------------------------------

pushd .
rem カレントディレクトリ=このバッチファイルのディレクトリ

call devenv DiagramEdit.sln /build "Release" 

popd
rem カレントディレクトリ=このバッチファイルのディレクトリ

rem  --------------------------------
rem (4)インストーラ
rem  --------------------------------


pushd .
rem カレントディレクトリ=このバッチファイルのディレクトリ

call devenv DiagramEdit.sln /build "Release" /project DiagramEdit_setup

popd
rem カレントディレクトリ=このバッチファイルのディレクトリ


