# pipex

`infile` から読み込んだ内容に対し 2 つのコマンドをパイプでつなぎ、結果を `outfile` に書き出す。

## ビルド
- 依存: 標準的な Unix 環境、`make`、`cc`、同梱の `libft`
- 通常ビルド: `make`
- デバッグビルド: `make debug`（`-g -O0` 付きで再ビルド）
- clean: `make clean` / `make fclean` / `make re`

## 使い方
```
./pipex infile "cmd1 [args]" "cmd2 [args]" outfile
```
`cmd1 < infile | cmd2 > outfile` と同等の挙動。コマンドは PATH 探索に加え、スラッシュを含むパス指定でも実行できる。`
infile` が開けない場合は `/dev/null` を入力として処理を続行し、`outfile` は作成または上書き。
