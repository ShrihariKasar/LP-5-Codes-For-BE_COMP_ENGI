# Assignment 10: Binary Classification using Deep Neural Networks
# Classify IMDB Movie Reviews into Positive and Negative Reviews

from tensorflow.keras.datasets import imdb
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Embedding, Flatten
from tensorflow.keras.preprocessing.sequence import pad_sequences

# Load IMDB Dataset
vocab_size = 10000

(X_train, y_train), (X_test, y_test) = imdb.load_data(num_words=vocab_size)

# Pad Sequences
max_length = 200

X_train = pad_sequences(X_train, maxlen=max_length)
X_test = pad_sequences(X_test, maxlen=max_length)

# Build Deep Neural Network Model
model = Sequential()

# Embedding Layer
model.add(Embedding(vocab_size, 32, input_length=max_length))

# Flatten Layer
model.add(Flatten())

# Hidden Layers
model.add(Dense(64, activation='relu'))
model.add(Dense(32, activation='relu'))

# Output Layer
model.add(Dense(1, activation='sigmoid'))

# Compile Model
model.compile(
    optimizer='adam',
    loss='binary_crossentropy',
    metrics=['accuracy']
)

# Train Model
model.fit(
    X_train,
    y_train,
    epochs=5,
    batch_size=128,
    validation_split=0.2,
    verbose=1
)

# Evaluate Model
loss, accuracy = model.evaluate(X_test, y_test)

print("\nTest Accuracy:", accuracy)

# Predict Sample Review
prediction = model.predict(X_test[:1])

print("\nPrediction Value:", prediction[0][0])

if prediction[0][0] > 0.5:
    print("Predicted Sentiment: Positive Review")
else:
    print("Predicted Sentiment: Negative Review")