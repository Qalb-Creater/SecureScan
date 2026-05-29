pipeline {
    agent any

    stages {

        stage('Build Scanner') {
            steps {
                sh 'mkdir -p build'
                sh 'g++ scanner.cpp -o build/scanner'
            }
        }

        stage('Test Scanner') {
            steps {
                sh './build/scanner 127.0.0.1'
            }
        }

        stage('Build Docker Image') {
            steps {
                sh 'sudo docker build -t securescan .'
            }
        }

        stage('Deploy Container') {
            steps {
                sh '''
                sudo docker stop securescan || true
                sudo docker rm securescan || true

                sudo docker run -d \
                -p 5000:5000 \
                --name securescan \
                securescan
                '''
            }
        }
    }
}
