# Assignment 11: Multiclass Classification using Deep Neural Networks
# OCR Letter Recognition using Deep Neural Network

import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.utils import to_categorical

# Load Dataset
# Kaggle Dataset File:
# letter-recognition.csv

data = pd.read_csv("letter-recognition.csv")

# Display First 5 Rows
print("\nDataset Preview:\n")
print(data.head())

# Features and Labels
# First column = letter
# Remaining columns = features

X = data.iloc[:, 1:].values
y = data.iloc[:, 0].values

# Encode Labels
encoder = LabelEncoder()

y_encoded = encoder.fit_transform(y)

# Convert Labels to One-Hot Encoding
y_categorical = to_categorical(y_encoded)

# Feature Scaling
scaler = StandardScaler()

X = scaler.fit_transform(X)

# Split Dataset
X_train, X_test, y_train, y_test = train_test_split(
    X,
    y_categorical,
    test_size=0.2,
    random_state=42
)

# Build Deep Neural Network
model = Sequential()

# Input + Hidden Layers
model.add(Dense(128, activation='relu', input_shape=(16,)))
model.add(Dropout(0.3))

model.add(Dense(64, activation='relu'))
model.add(Dropout(0.3))

model.add(Dense(32, activation='relu'))

# Output Layer (26 Alphabets)
model.add(Dense(26, activation='softmax'))

# Compile Model
model.compile(
    optimizer='adam',
    loss='categorical_crossentropy',
    metrics=['accuracy']
)

# Model Summary
print("\nModel Summary:\n")
model.summary()

# Train Model
history = model.fit(
    X_train,
    y_train,
    epochs=20,
    batch_size=32,
    validation_split=0.2,
    verbose=1
)

# Evaluate Model
loss, accuracy = model.evaluate(X_test, y_test)

print("\nTest Accuracy:", accuracy)

# Predict Sample
prediction = model.predict(X_test[:1])

predicted_class = np.argmax(prediction)

predicted_letter = encoder.inverse_transform([predicted_class])[0]

print("\nPredicted Letter:", predicted_letter)

# Display Actual Letter
actual_class = np.argmax(y_test[0])

actual_letter = encoder.inverse_transform([actual_class])[0]

print("Actual Letter:", actual_letter)