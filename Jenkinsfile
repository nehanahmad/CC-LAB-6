pipeline {
    agent any

    stages {

        stage('Build Backend Image') {
            steps {
                sh '''
                docker rm -f backend1 backend2 nginx-lb || true
                docker rmi -f backend-app || true

                cd backend
                docker build -t backend-app .
                '''
            }
        }

        stage('Run Backend Containers') {
            steps {
                sh '''
                docker network create app-network || true

                docker run -d --name backend1 --network app-network backend-app
                docker run -d --name backend2 --network app-network backend-app
                '''
            }
        }

        stage('Run NGINX Load Balancer') {
            steps {
                sh '''
                docker rm -f nginx-lb || true

                docker run -d \
                  --name nginx-lb \
                  --network app-network \
                  -p 80:80 \
                  nginx

                docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf
                docker exec nginx-lb nginx -s reload
                '''
            }
        }
    }

    post {
        success {
            echo '✅ Backend + NGINX deployed successfully'
        }
        failure {
            echo '❌ Pipeline failed'
        }
    }
}
