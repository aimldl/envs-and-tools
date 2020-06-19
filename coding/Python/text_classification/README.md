##### aimldl > python3 > text_classification >  README.md

[TensorFlow Dataset/imdb_reviews](https://www.tensorflow.org/datasets/catalog/imdb_reviews)
```
Large Movie Review Dataset. This is a dataset for binary sentiment classification containing substantially more data than previous benchmark datasets. We provide a set of 25,000 highly polar movie reviews for training, and 25,000 for testing. There is additional unlabeled data for use as well.

URL: http://ai.stanford.edu/~amaas/data/sentiment/
DatasetBuilder: tfds.text.imdb.IMDBReviews
imdb_reviews is configured with tfds.text.imdb.IMDBReviewsConfig and has the following configurations predefined (defaults to the first one):

plain_text (v0.1.0) (Size: 80.23 MiB): Plain text

bytes (v0.1.0) (Size: 80.23 MiB): Uses byte-level text encoding with tfds.features.text.ByteTextEncoder

subwords8k (v0.1.0) (Size: 80.23 MiB): Uses tfds.features.text.SubwordTextEncoder with 8k vocab size

subwords32k (v0.1.0) (Size: 80.23 MiB): Uses tfds.features.text.SubwordTextEncoder with 32k vocab size
```
